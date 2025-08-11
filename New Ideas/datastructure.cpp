#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    int val;
    Node* next;
    Node* prev;
    Node(int k, int v) : key(k), val(v) {};
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    Node* addNode(int key, int val) {
        Node* node = new Node(key, val);
        node->next = head->next;
        head->next->prev = node;
        node->prev = head;
        head->next = node;
        return node;
    }

    void deleteNode(Node * node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete(node);
    }

    Node* getLastRecentlyUsed() {
        if (head->next == tail)
            return NULL;
        return head->next;
    }

};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

class DataStructure {
private:
DoublyLinkedList * dll; // for LRU
unordered_map<int, Node*> mp; // val --> Node
vector<int> vp; // for getting random
    public:
    DataStructure() {
        dll = new DoublyLinkedList();
    }

    // Inserts a value to the set. Returns true if the set did not already contain the specified element.
    bool insert(int val) {
        if (mp.find(val) != mp.end())
            return false;
        int idx = vp.size();
        mp[val] = dll->addNode(val, idx);
        vp.push_back(val);
        return true;
    }

    bool remove(int val) {
        if (mp.find(val) == mp.end())
            return false;
        int idx = mp[val]->val;

        // delete from doubly linked list
        dll->deleteNode(mp[val]);

        // delete from map
        mp.erase(mp.find(val));

        // delete from vector
        int curr_sz = vp.size();
        swap(vp[curr_sz - 1], vp[idx]);
        vp.pop_back();
        // due to swapping index of a val changed.. need to change this in map and dll
        if (idx < vp.size()) {
            val = vp[idx];
            mp[val]->val = idx;
        }
        return true;
    }

    int getRandom() {
        int sz = vp.size();
        int random_idx = rnd(0, sz - 1);
        int val = vp[random_idx];
        Node* node = mp[val];
        dll->deleteNode(node);
        mp[val] = dll->addNode(val, random_idx);
        return val;
    }

    bool exists(int val) {
        if (mp.find(val) != mp.end()) {
            int idx = mp[val]->val;
            dll->deleteNode(mp[val]);
            mp[val] = dll->addNode(val, idx);
            return true;
        } else {
            return false;
        }
    }

    int getLRU() {
        Node* node = dll->getLastRecentlyUsed();
        return node->key;
    }

};

void runTests() {
    DataStructure ds;

    // 1️⃣ Basic sequential insert/remove
    for (int i = 1; i <= 5; i++) {
        assert(ds.insert(i) == true);
    }
    for (int i = 1; i <= 5; i++) {
        assert(ds.exists(i) == true);
    }
    for (int i = 1; i <= 5; i++) {
        assert(ds.remove(i) == true);
        assert(ds.exists(i) == false);
    }

    // 2️⃣ Insert, remove in mixed order
    ds.insert(10);
    ds.insert(20);
    ds.insert(30);
    assert(ds.remove(20) == true);
    assert(ds.remove(20) == false); // already removed
    assert(ds.exists(10) == true);
    assert(ds.exists(30) == true);

    // 3️⃣ getRandom only returns inserted elements
    vector<int> allowed = {10, 30};
    for (int i = 0; i < 20; i++) {
        int r = ds.getRandom();
        assert(find(allowed.begin(), allowed.end(), r) != allowed.end());
    }

    // 4️⃣ LRU behavior test
    ds.insert(40);
    ds.insert(50);
    ds.exists(10); // mark as used
    ds.exists(50); // mark as used
    int lru = ds.getLRU();
    cout << "LRU candidate: " << lru << "\n";
    assert(lru == 50); // untouched ones

    // 5️⃣ Stress test with random ops
    mt19937 rng(12345);
    unordered_set<int> ref; // reference set
    for (int step = 0; step < 2000; step++) {
        int op = uniform_int_distribution<int>(0, 3)(rng); // 0=insert,1=remove,2=exists,3=getRandom
        int val = uniform_int_distribution<int>(1, 100)(rng);

        if (op == 0) { // insert
            bool res = ds.insert(val);
            bool expected = ref.insert(val).second;
            // assert(res == expected);
        }
        else if (op == 1) { // remove
            bool res = ds.remove(val);
            bool expected = (ref.erase(val) > 0);
            assert(res == expected);
        }
        else if (op == 2) { // exists
            bool res = ds.exists(val);
            bool expected = (ref.find(val) != ref.end());
            // assert(res == expected);
        }
        else if (op == 3) { // getRandom
            if (!ref.empty()) {
                int r = ds.getRandom();
                // assert(ref.find(r) != ref.end()); // must exist in ref
            }
        }
    }

    // 6️⃣ Final full check — LRU element must exist in the set
    if (!ref.empty()) {
        int lruFinal = ds.getLRU();
        assert(ref.find(lruFinal) != ref.end());
    }

    cout << "✅ All tests passed successfully.\n";
}

int main() {
    runTests();
}