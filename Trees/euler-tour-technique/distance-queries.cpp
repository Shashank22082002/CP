// https://atcoder.jp/contests/abc294/tasks/abc294_g

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
const int lg = 17;
template<typename T>
struct Fenwick {
    vector<T> BIT;
    int n;
    Fenwick() : BIT(), n(0) {};
    Fenwick(int _n) {
        n = _n;
        BIT = vector<T> (n);
    }
    void clear() {
        BIT = vector<T> (n, T());
    }
    void add(int id, T val) {
        for (; id < n; id += (id & (-id)))
            BIT[id] += val;
    }
    T sum(int id) {
        // sum from 1 .. id
        T sum = T();
        for (; id > 0; id -= (id & (-id)))
            sum += BIT[id];
        return sum;
    }
    T getSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

Fenwick<int> ft;
vector<vector<int>> g, f;
map<int, map<int, int>> wt;
vector<int> in, out, euler, dis, par;
int timer, n;

void euler_tour(int u, int p) {
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        in[v] = ++timer;
        euler.push_back(wt[u][v]);
        euler_tour(v, u);
        out[v] = ++timer;
        euler.push_back(-wt[u][v]);
    }
}


void dfs(int u, int p) {
    par[u] = p;
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        dis[v] = dis[u] + 1;
        dfs(v, u);
    }
}

void init() {
    // f[0][i] = par[i];
    // f[1][i] = par[par[i]];
    // f[2][i] = par[par[par[par[i]]]];
    dfs(1, 0);
    f = vector<vector<int>> (lg + 1, vector<int> (n + 1));
    f[0] = par;
    for (int i = 0; i < lg; i++) {
        for (int j = 1; j <= n; j++) {
            f[i + 1][j] = f[i][f[i][j]];
        }
    }
}

int KthAncestor(int u, int k) {
    for (int i = lg; i >= 0; i--) {
        if (((1 << i) & k) > 0)
            u = f[i][u]; 
    }
    return u;
}

int LCA(int u, int v) {
    if (dis[u] > dis[v]) {
        u = KthAncestor(u, dis[u] - dis[v]);
    } else {
        v = KthAncestor(v, dis[v] - dis[u]);
    }
    if (u == v)
        return u;
    for (int i = lg; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }
    return f[0][u];
}

int distance(int u, int v) {
    int lca = LCA(u, v);
    return ft.getSum(in[1], in[u]) + ft.getSum(in[1], in[v]) - 2 * ft.getSum(in[1], in[lca]);
}

void solve() {
    int u, v, w, q, t, id;
    cin >> n;
    g = vector<vector<int>> (n + 1);
    in = out = dis = par = vector<int> (n + 1);
    vector<pair<int, int>> edg;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w;
        g[u].push_back(v);
        g[v].push_back(u);
        edg.push_back({u, v});
        wt[u][v] = wt[v][u] = w;
    }
    // euler.push_back(0);
    euler.push_back(0);
    euler_tour(1, 0);
    assert(timer == euler.size() - 1);
    ft = Fenwick<int> (timer + 1);
    for (int i = 1; i <= timer; i++) {
        ft.add(i, euler[i]);
    }
    init();
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> id >> w;
            --id;
            u = edg[id].first, v = edg[id].second;
            if (v == par[u])
                swap(u, v);
            ft.add(in[v], w - wt[u][v]);
            ft.add(out[v], wt[v][u] - w);
            wt[u][v] = wt[v][u] = w;
        } else {
            cin >> u >> v;
            cout << distance(u, v) << endl;
        }
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