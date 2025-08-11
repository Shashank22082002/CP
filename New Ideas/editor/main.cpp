// coding a text editor
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()


struct Node {
    string data;
    int len; // data.length()
    int leftLength;
    Node* left;
    Node* right;
    Node* parent;
};

class BinaryTree {
private:
    Node* root;
    stack<Operation> ops;

public:
    BinaryTree() {
        root = new Node();
        root->len = 0;
        root->leftLength = 0;
    }

    void insert(const string &s, int off) {
        insert(root, s, off);
    }

    Node* insert(Node* node, const string &s, int off) {
        // rebalancing later.
        if (node->leftLength > off) {
            node->left = insert(node->left, s, off);
            node->leftLength += s.length();
        } else if (node->leftLength + len >= off) {
            node = insertAtNode(node, s, off);
        } else {
            node->right = insert(node->right, s, off - node->leftLength - len);
        }
        return node;
    }

    Node* insertAtNode(Node* node, const string &s, int off) {
        // insert string in node's data
        string data = node->data;
        int pos = off - node->leftLength;
        string res = data.substr(0, pos);
        res += s;
        res += data.substr(pos, node->len - pos);
        node->data = res;
        node->len = res.length();

        // split node (Later)
        // maintain undo operation in stack
        return node;
    }

    void delete(int off, int len) {
        delete(root, off, len);
    }

    Node* delete(Node* node, int off, int len) {
        if (node->leftLength > off) {
            node->left = deleteNode(node->left, s, off);
        } else if (node->leftLength + len >= off) {
            node = deleteAtNode(node, off, len);
        } else {
            node->right = deleteNode(node->right, off, len);
        }
        return node;
    }

    Node* deleteAtNode(Node* node, int off, int len) {
        string data = node->data;
        int pos = off - node->leftLength;
        // handle case when rest string length exceeds len
        if (node->len - pos >= len) {
            // completely lies in this node
            node->data = data.substr(0, pos) + data.substr(pos + len, node->len - pos - len);
        } else {
            node->data = data.substr(0, pos);
            node->right = delete(node->right, off + node->len - pos, len - node->len + pos);
        }
        return node;
    }

};


void solve() {
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}