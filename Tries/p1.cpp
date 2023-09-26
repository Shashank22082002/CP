// https://codeforces.com/contest/1864/problem/E

#include <bits/stdc++.h>
using namespace std;
#define intt int32_t
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
typedef long long ll;
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}
 
 
#define showVVI(arr)           \
{                              \
    for (auto &vvv : arr)      \
    {                          \
        for (auto &xxxx : vvv) \
            csp(xxxx);         \
        cout << endl;          \
    }                          \
}
 
const int INF = 2e9 + 7;
const int MOD = 998244353;

struct Node {
    Node* links[2];
    // prefOnes till now from the root
    int prefOnes = 0;
    int numCount = 0;
    Node(int _prefOnes) {
        prefOnes = _prefOnes;
        numCount = 0;
        links[0] = links[1] = NULL;
    }
    bool containsKey(int bit) {
        assert(bit < 2);
        return (links[bit] != NULL);
    }
    Node* getLink(int bit) {
        return links[bit];
    }
    void put(int bit, Node *node) {
        links[bit] = node;
    }
};

class Trie {
public:
    // ctor
    Trie() {
        root = new Node(0);
    }

    void insert(int num) {
        // insert a number in the trie
        Node* node = root;
        (node->numCount)++;
        for(int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(!node->containsKey(bit)) {
                node->put(bit, new Node(node->prefOnes + bit));
            }
            node = node->getLink(bit);
            (node->numCount)++;
        }
    }

    int f(Node* node) {
        int prefs = node->prefOnes;
        if(node->containsKey(0) && node->containsKey(1)) {
            return (2*prefs + 1) * node->getLink(0)->numCount * node->getLink(1)->numCount + 
            f(node->getLink(0)) + f(node->getLink(1));
        }
        if(node->containsKey(0)) {
            return f(node->getLink(0));
        }
        if(node->containsKey(1)) {
            return f(node->getLink(1));
        }
        return node->numCount * node->numCount * prefs;
    }

    int calculate() {
        assert(root != NULL);
        return f(root);
    }
    
private:
    Node * root;
};

int binpow(int a, int b) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    Trie* trie = new Trie();
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        trie->insert(v[i]);
    }
    int num = trie->calculate();
    int den = n*n;
    int g = __gcd(num, den);
    num /= g;
    den /= g;
    cout << ((num * binpow(den, MOD-2)) + 1) % MOD << endl;
}

intt main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++) 
        solve();
    return 0;
}