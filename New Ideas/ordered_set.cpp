#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

struct Node {
    int key;
    int freq;
    int sum;
    Node* left;
    Node* right;
    Node(int _key) {
        key = _key;
        freq = 1;
        sum = 1;
        left = nullptr;
        right = nullptr;
    }

    void inc() {
        freq++;
    }

    int getFreq() {
        return freq;
    }

    void incSum() {
        sum++;
    }

    int getSum() {
        return sum;
    }
};

struct BST {
private:
    Node* root;

public:
    BST() {
        root = NULL;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    Node* insert(Node* node, int key) {
        if (node == NULL) {
            node = new Node(key);
            return node;
        }
        if (node->key > key) {
            // go Left
            node->left = insert(node->left, key);
        } else if (node->key < key) {
            // go Right
            node->right = insert(node->right, key);
        } else {
            node->inc();
        }
        node->incSum();
        return node;
    }

    bool find(int key) {
        return find(root, key);
    }

    bool find(Node* node, int key) {
        if (!node)
            return false;
        if (node->key > key) {
            return find(node->left, key);
        } else if (node->key < key) {
            return find(node->right, key);
        }
        return true;
    }

    int findOrder(int key) {
        // find the order of key -- number of values that are strictly less than the key
        // would need to maintain sums of frequencies as well
        return findOrder(root, key);
    }

    int findOrder(Node* node, int key) {
        if (!node) {
            return 0;
        }
        if (node->key >= key) {
            return findOrder(node->left, key);
        } else {
            int leftSum = (node->left ? node->left->getSum() : 0);
            // cout << "At node : " << node->key << " " << node->getFreq() << endl;
            int sum = leftSum + node->getFreq() + findOrder(node->right, key);
            // cout << "Returning sum " << sum << endl;
            return sum;
        }
    }

    int size() {
        return root ? root->getSum() : 0;
    }
};

class OrderedSet {
private:
    BST* bst;

public:
    OrderedSet() {
        bst = new BST();
    }

    void insert(int key) {
        bst->insert(key);
    }

    bool find(int key) {
        return bst->find(key);
    }

    int findOrder(int key) {
        return bst->findOrder(key);
    }

    int size() {
        return bst->size();
    }
};

void solve() {
    vector<int> v = {30, 52, 18, 103, 81, 20, 128};
    OrderedSet oset;
    // oset.insert(10);
    // oset.insert(20);
    // cout << oset.findOrder(14) << endl;
    // oset.insert(7);
    // oset.insert(10);
    // cout << oset.findOrder(10) << endl;
    for (auto &val : v) {
        oset.insert(val);
        int order = oset.findOrder(val);
        int sz = oset.size();
        int rank = sz - order;
        cout << rank << " " << sz << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}