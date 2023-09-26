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
    int prefOnes = 0;
    int numCount = 0;
};

Node* root;

void insert(int num) {
    // insert a number in the trie
    Node* node = root;
    (node->numCount)++;
    for(int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if(!node->links[bit]) {
            node->links[bit] = new Node();
            node->links[bit]->prefOnes = node->prefOnes + bit;
        }
        node = node->links[bit];
        (node->numCount)++;
    }
}

int f(Node* node) {
    int prefs = node->prefOnes;
    Node* l = node->links[0];
    Node* r = node->links[1];
    if(l && r) {
        return (2*prefs + 1) * (l->numCount) * (r->numCount) + 
        f(l) + f(r);
    }
    if(l) {
        return f(l);
    }
    if(r) {
        return f(r);
    }
    return node->numCount * node->numCount * prefs;
}

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
    root = new Node();
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        insert(v[i]);
    }
    int num = f(root);
    int den = n*n;
    int g = __gcd(num, den);
    num /= g;
    den /= g;
    cout << (((num % MOD) * binpow(den, MOD-2)) % MOD + 1) % MOD << endl;
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