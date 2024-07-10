// https://codeforces.com/contest/1575/problem/I
// 2300 :) solved with ease

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(v) v.begin(), v.end()
const int MOD = 1E9 + 7;

#define show(arr)          \
{                          \
    for (auto &_x : arr)   \
        cout << _x << " "; \
    cout << endl;          \
}


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


int n, q, tim;
vector<vector<int>> g;
vector<int> in, out, euler, a;

void euler_tour(int u, int p = 1) {
    euler.push_back(a[u]);
    in[u] = ++tim;
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        euler_tour(v, u);
    }
    euler.push_back(-a[u]);
    out[u] = ++tim;
}

// tested on cses
int x = 1; // take input, x is root
const int lg = 17;
vector<vector<int>> f; // initialise g
vector<int> p, dis;

void dfs(int u) {
    for (auto &v: g[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        dis[v] = dis[u] + 1;
        dfs(v);
    }
}

void init() {
    p = dis = vector<int> (n+1);
    f = vector<vector<int>> (lg + 1, vector<int> (n + 1));
    dfs(x); // root x
    p[x] = x;
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

int distance(int u, int v, Fenwick<int> &ft) {
    int lca = LCA(u, v);
    return ft.getSum(1, in[u]) + ft.getSum(1, in[v]) - 2*ft.getSum(1, in[lca]) + a[lca];
}


void solve() {
    int u, v, t, c;
    cin >> n >> q;
    a = vector<int> (n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    in = out = vector<int> (n + 1);
    g = vector<vector<int>> (n + 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    euler.push_back(0);
    euler_tour(1);
    // show(euler);
    // show(in);
    // show(out);
    Fenwick<int> ft(euler.size());
    for (int i = 1; i < euler.size(); i++)
        ft.add(i, euler[i]);
    init();
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> u >> c;
            c = abs(c);
            ft.add(in[u], c - a[u]);
            ft.add(out[u], a[u] - c);
            a[u] = c;
        } else {
            cin >> u >> v;
            int dis = distance(u, v, ft);
            cout << 2 * dis - a[u] - a[v] << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++)
        solve();
}