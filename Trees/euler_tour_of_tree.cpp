// https://codeforces.com/contest/1675/problem/F
// nice concept of removing leaf nodes 1 by one to traverse the tree
// sort of euler tour of the tree, with selected vertices..
// Another similar problem -- same concept https://leetcode.com/problems/collect-coins-in-a-tree/description/
// Concept is removing unused edges, to get the required "subtree" on which euler tour is asked..

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
 
int INF = 1e18 + 7;

void dfs(int u, int p, vector<set<int>> &g, vector<int> &par) {
    par[u] = p;
    for(auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u, g, par);
    }
}

void dfs2(int u, int p, vector<set<int>> &g, vector<int> &d) {
    for (auto &v: g[u]) {
        if (v == p) continue;
        d[v] = d[u] + 1;
        dfs2(v, u, g, d);
    }
}


void solve() {
    int n, k, x, y, u, v;
    cin >> n >> k;
    cin >> x >> y;
    set<int> a;
    a.insert(x);
    a.insert(y);
    for(int i = 0; i < k; ++i) {
        cin >> u;
        a.insert(u);
    }
    vector<set<int>> g(n+1);
    queue<int> q;
    vector<int>  par(n+1), d(n+1);
    for(int i = 0; i < n-1; ++i) {
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    for (int i = 1; i <= n; ++i) {
        if(a.find(i) != a.end()) continue;
        if(g[i].size() == 1) {
            q.push(i);
            // cout << i << endl;
        }
    }
    dfs(x, 0, g, par);
    // show(par);
   
    while(!q.empty()) {
        int leaf = q.front();
        q.pop();
        int parent = par[leaf];
        g[leaf].erase(parent);
        g[parent].erase(leaf);
        if(a.find(parent) == a.end() && g[parent].size() == 1)
            q.push(parent);
    }
    dfs2(x, 0, g, d);
    // show(d);
    int edges = 0;
    for (auto &n: g) {
        edges += n.size();
    }
    // cout << edges << " " << d[y] << endl;
    cout << edges - d[y] << endl;
}
 
intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++) solve();
    return 0;
}