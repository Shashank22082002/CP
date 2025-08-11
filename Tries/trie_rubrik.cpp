#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

struct Node {
    Node* links[26];
    // cts[i] tells number of strings that will end at i more depth from this node
    int cts[64] = {0};

    void put(char ch, Node* node, int suff) {
        links[ch - 'a'] = node;
        if (suff < 64)
            cts[suff] += 1;
    }

    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    int getSuffCount(int len) {
        return cts[len];
    }

    void terminate() {
        cts[0] += 1;
    }
};

class Trie {
private:
    Node * root;
public:
    Trie () {
        root = new Node();
    }

    void insert(string s) {
        Node * curr = root;
        for (int i = 0; i < s.length(); i++) {
            if (!curr->containsKey(s[i])) {
                curr->put(s[i], new Node(), s.length() - i);
            }
            curr = curr->get(s[i]);
        }
        curr->terminate();
    }

    int query(string prefix, int suffix) {
        // returns number of strings with prefix and having a length of suffix following them
        Node * curr = root;
        for (char c : prefix) {
            if (!curr->containsKey(c)) {
                return 0;
            }
            curr = curr->get(c);
        }
        return curr->getSuffCount(suffix);
    }
};

void solve() {
    int n, q;
    string s;
    cin >> n >> q;
    Trie trie;
    for (int i = 0; i < n; i++) {
        cin >> s;
        trie.insert(s);
    }

    for (int i = 0; i < q; i++) {
        cin >> s;
        string pref = "";
        string num = "";
        for (char c : s) {
            if (c <= 'z' && c >= 'a') {
                pref += c;
            } else {
                num += c;
            }
        }
        int suffLen = stoi(num);
        int suffCount = trie.query(pref, suffLen);
        if (suffCount == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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