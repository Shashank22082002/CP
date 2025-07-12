// https://atcoder.jp/contests/arc201/tasks/arc201_c
// Set closure problem

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

int binPow(int a, int b, int m) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

struct TrieNode {
    TrieNode* links[2];
    int cnt = 0;
    bool flag = false;
    int dp = 0;
    // dp denotes the number of subsets of current dict, that can form closure for current prefix*
    bool containsKey(char key) {
        return links[key - 'A'] != NULL && cnt != 0;
    }
    void put(char key, TrieNode* node) {
        links[key - 'A'] = node;
    }
    TrieNode* get(char key) {
        return links[key - 'A'];
    }
    void increaseCount() {
        cnt += 1;
    }
    void decreaseCount() {
        cnt -= 1;
    }
    void updateDP() {
        int dpLeft = links[0] != NULL ? links[0]->dp : 0;
        int dpRight = links[1] != NULL ? links[1]->dp : 0;
        dp = (dpLeft * dpRight % MOD + flag * binPow(2, cnt, MOD)) % MOD;
    }
};

struct Trie {
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    int insert(string &s) {
        TrieNode* curr = root;
        vector<TrieNode*> path = {root};
        for (char c : s) {
            if (!curr->containsKey(c)) {
                curr->put(c, new TrieNode());
            }
            curr->increaseCount();
            curr = curr->get(c);
            path.push_back(curr);
        }
        curr->flag = true;
        
        while (!path.empty()) {
            TrieNode* node = path.back();
            node->updateDP();
            path.pop_back();
        }
        return root->dp;

    }

    bool isPrefix(string &s) {
        // check if s is prefix of any string in the dictionary
        TrieNode* curr = root;
        for (char c : s) {
            if (!curr->containsKey(c)) {
                return false;
            }
            curr = curr->get(c);
        }
        return true;
    }
    
};

void solve() {
    int n;
    cin >> n;
    string s;
    Trie dict;
    for (int rep = 0; rep < n; rep++) {
        cin >> s;
        cout << dict.insert(s) << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}