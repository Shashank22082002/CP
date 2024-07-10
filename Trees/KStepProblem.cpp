// https://atcoder.jp/contests/abc267/tasks/abc267_f
// query(u, k) -- find a vertice which is k distance away from u

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(v) v.begin(), v.end()
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

const int N = 1E6 + 5;
const int INF = 1E9;


class RootedTree {
    int n, root, lg = 17;
    vector<vector<int>> g, f;
    vector<int> p, dis;
public:
    RootedTree(int _n, vector<vector<int>> &adj, int r = 1) {
        n = _n;
        root = r;
        g = adj;
    }
    void dfs(int u) {
        for (auto &v: g[u]) {
            if (v == p[u]) continue;
            p[v] = u;
            dis[v] = dis[u] + 1;
            dfs(v);
        }
    }
    void init() {
        p = dis = vector<int> (n + 1);
        f = vector<vector<int>> (lg + 1, vector<int> (n + 1));
        dfs(root); // root x
        p[root] = 0;
        f[0] = p; // 2^0th parent
        for (int i = 0; i < lg; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i+1][j] = f[i][f[i][j]]; // 2^(i+1)th parent;
            }
        }
    }
    int KthAncestor(int u, int k) {
        for (int i = lg; i >= 0; --i) {
            if((k >> i) & 1) u = f[i][u];
        }
        return u;
    }
    
    int LCA(int u, int v) {
        if (dis[u] > dis[v])
            u = KthAncestor(u, dis[u] - dis[v]);
        else
            v = KthAncestor(v, dis[v] - dis[u]);
        if (u == v) return u;
        for (int i = lg; i >= 0; --i) {
            if(f[i][u] != f[i][v]) {
                u = f[i][u];
                v = f[i][v];
            }
        }
        return f[0][u];
    }
    
    int distance(int u, int v) {
        return dis[u] + dis[v] - 2*dis[LCA(u, v)];
    }
};

vector<int> bfs(int r, int n, vector<vector<int>> &g) {
    vector<int> dis(n + 1, -1);
    queue<int> q;
    dis[r] = 0;
    q.push(r);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &v: g[u]) {
            if (dis[v] == -1) {
                q.push(v);
                dis[v] = dis[u] + 1;
            }
        }
    }
    return dis;
}

void solve() {
    int n, u, v, q, k;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> v1 = bfs(1, n, g);
    int d1 = max_element(all(v1)) - v1.begin();
    vector<int> v2 = bfs(d1, n, g);
    int d2 = max_element(all(v2)) - v2.begin();
    RootedTree t1(n, g, d1);
    RootedTree t2(n, g, d2);
    t1.init();
    t2.init();
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> u >> k;
        int v1 = t1.KthAncestor(u, k);
        int v2 = t2.KthAncestor(u, k);
        if (v1)
            cout << v1 << endl;
        else if (v2)
            cout << v2 << endl;
        else
            cout << -1 << endl;
    }
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int _t = 0; _t < t; _t++) {
        solve();
    }
    return 0;
}