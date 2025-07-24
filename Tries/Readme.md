## Trie Data Structure

### Trie Visualisation -- Imp Read this while revising

### 📌 **Trie is a compressed Dictionary**

Think of try as a dictionary or collection of words, where we group prefixes.. and store in a N-Ary Tree

Since we talk about Tree -- what are nodes and what are edges??

### 📌 **Trie Node represents a prefix**

Each node represents a complete prefix stop in a string/number you're building.

This directly means -- We can store properties of a prefix inside a node.

- Eg (Most Useful and common) : How many words are there in the dictionary with given prefix

- Eg (Used in a problem) : How many words are needed so that we have minimum cover for prefix -- DP over above property

E.g., `node` at depth 2 in left path = prefix `"01"` = bits `[0,1]`

### 📌 **Links represent words or bits**

- Link `0` → go left
- Link `1` → go right
    
    Think of it like navigating a binary tree where decisions are guided by each bit.
    

Re-iterating over cnt.. since it is useful and easy to mess up with
### 📌 **`cnt` = number of inserted numbers that have this prefix**

Helps answer queries like:

- "How many numbers begin with `10`?"
- "How many numbers have XOR with `x` < `k`?" (you sum whole subtrees using `cnt`)



### `1. Alphabet Trie`
```cpp
struct Node {
    Node* links[26];
    int cnt;
    bool flag = false;
    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
    }
    Node* get(char ch) {
        return links[ch - 'a'];
    }
    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }
    void setEnd() {
        flag = true;
    }
    bool isEnd() {
        return flag;
    }
};

class Trie {
public:
    Node* root;
    Trie() {
        root = new Node();
    }
    /** Insert a word in trie in O(len) */
    void insert(string &s) {
        Node* node = root;
        node->cnt++;
        for (auto &c: s) {
            if (!node->containsKey(c)) {
                node->put(c, new Node());
            }
            node = node->get(c);
            node->cnt++;
        }
        node->setEnd();
    }
    
    bool search(string &s) {
        Node* node = root;
        for (auto &c: s) {
            if (!node->containsKey(c)) {
                return false;
            }
            node = node->get(c);
        }
        return node->isEnd();
    }
};

```

### `2. Bit Trie`
```cpp
// tested for insertion and deletion
struct Node {
    Node* links[2];
    int cnt;
    bool containsKey(int bit) { return (links[bit] != NULL) && (links[bit]->cnt); }
    Node *get(int bit) { return links[bit]; }
    void put(int bit, Node* node) { links[bit] = node; }
};

class TRIE {
private:
    Node * root;
    int mxb;
public:
    TRIE(int b = 31) {
        root = new Node();
        mxb = b;
    }
    void insert(const int &num) {
        Node* node = root;
        for (int i = mxb; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit)) {
                node->put(bit, new Node());
            }
            node = node -> get(bit);
            node->cnt ++;
        }
    }
    
    bool search(const int &num) {
        Node* node = root;
        for (int i = mxb; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit))
                return false;
            node = node -> get(bit);
        }
        return true;
    }
    
    void remove(const int &num) {
        Node* node = root;
        for (int i = mxb; i >= 0; i--) {
            int bit = (num >> i) & 1;
            assert(node->containsKey(bit));
            node = node->get(bit);
            node->cnt--;
        }
    }
    
    int maxXor(const int &num) {
        Node* node = root;
        int res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->containsKey(!bit)) {
                node = node -> get(!bit);
                res += (1 << i);
            } else {
                node = node -> get(bit);
            }
        }
        return res;
    }
    
    int minXor(const int &num) {
        Node* node = root;
        int res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->containsKey(bit)) {
                node = node -> get(bit);
            } else {
                node = node -> get(!bit);
                res += (1 << i);
            }
        }
        return res;
    }
    
    void PrintTrie() {
        Node* node = root;
        PrintTrieRecursive(node, 0);
    }
    
    void PrintTrieRecursive(Node* root, int depth) {
        for (int i = 0; i < depth; i++)
            cout << '\t';
        cout << "Count: " << root->cnt << endl;
        if (root->containsKey(0)) {
            for (int i = 0; i < depth; i++)
            cout << '\t';
            cout << "Link 0 :\n";
            PrintTrieRecursive(root->get(0), depth + 1);
        };
        if (root->containsKey(1)) {
            for (int i = 0; i < depth; i++)
            cout << '\t';
            cout << "Link 1 :\n";
            PrintTrieRecursive(root->get(1), depth + 1); 
        }
    }
};
```

### `3. Implementation without using pointers`
https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap

### `Problems solved: `
https://codeforces.com/problemset/problem/1902/E

https://atcoder.jp/contests/arc201/tasks/arc201_c

https://leetcode.com/problems/count-pairs-with-xor-in-a-range/


## Concepts
### `DP with Trie: `
- Visualise Trie like a binary or N-ary tree
- Maintain dp value with each trie node
```cpp
struct TrieNode {
    int cnt = 0;
    int dp = 0;
    bool end = false;
    TrieNode* links[2];
    // Other methods...


    void updateDP() {
        // updates dp based on child dp values
        int dpLeft = links[0] != NULL ? links[0] -> dp : 0;
        int dpRight = links[1] != NULL ? links[1] -> dp : 0;
        dp = f(dpLeft, dpRight);
    }
}