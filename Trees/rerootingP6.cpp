// https://codeforces.com/contest/1882/problem/D
// seems boring now :|

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> g;
vector<int> h, f, sz, a;

void calcSize(int u, int p) {
    sz[u] = 1;
    for (auto &v: g[u]) {
        if (v == p) continue;
        calcSize(v, u);
        sz[u] += sz[v];
    }
}

void dfs(int u, int p) {
    int ans = 0;
    for (auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        ans += f[v];
    }
    f[u] = ans + (a[u] ^ a[p]) * sz[u];
}

void reroot(int u, int p) {
    h[u] = f[u];
    for (auto &v: g[u]) {
        if (v == p) continue;
        int init_fu = f[u], init_fv = f[v], init_szu = sz[u], init_szv = sz[v];
        f[u] -= f[v];
        f[u] += (a[u] ^ a[v]) * (sz[u] - sz[v]);
        f[v] -= (a[u] ^ a[v]) * (sz[v]);
        f[v] += f[u];
        sz[u] -= sz[v];
        sz[v] += sz[u];
        reroot(v, u);
        f[u] = init_fu, f[v] = init_fv, sz[u] = init_szu, sz[v] = init_szv;
    }
}

void solve() {
    int n, u, v;
    cin >> n;
    h = f = sz = a = vector<int> (n + 1);
    g = vector<vector<int>> (n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    calcSize(1, 1);
    dfs(1, 1);
    reroot(1, 1);
    for (int i = 1; i <= n; i++) {
        cout << h[i] << ' ';
    }
    cout << endl;
}

signed main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    int _t;
    cin >> _t;
    for (int i = 0; i < _t; i++) {
        solve();
    }
}