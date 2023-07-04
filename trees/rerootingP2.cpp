/**
 * Gardening Friends -- https://codeforces.com/problemset/problem/1822/F
 * Small modified verison of P1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> g;
vector<int> f, h, d;
vector<ll> pf;
int t, n, k, c;

void dfs(int u, int p) {
    d[u] = d[p] + 1;
    for (auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        f[u] = max(1 + f[v], f[u]);
    }
}

void reroot(int u, int p) {
    // initial root is u..
    int argmax = -1;
    h[u] = f[u];
    pf[u] = h[u] * 1ll * k - c * 1ll * (d[u] - d[1]);
    for (auto &ch: g[u]) {
        if (h[u] == 1 + f[ch])
            argmax = ch;
    }

    for (auto &v: g[u]) {
        if (v == p) continue;
        // rerooting from u to v
        int init_fu = f[u], init_fv = f[v];
        if (v == argmax) {
            f[u] = 0;
            for (auto &ch: g[u]) {
                if (ch == v) continue;
                f[u] = max(f[u], 1 + f[ch]);
            }
        }
        f[v] = max(1 + f[u], f[v]);
        reroot(v, u);
        f[u] = init_fu, f[v] = init_fv;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n >> k >> c;
        g = vector<vector<int>> (n+1);
        d = f = h = vector<int> (n+1);
        pf = vector<ll> (n+1);
        int u, v;
        for (int i = 0; i < n - 1; ++i) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        // compute fu(x) wrt some u, lets say 1...
        // h[u] = fu(u)
        dfs(1, 0);
        reroot(1, 0);

        cout << *max_element(pf.begin(), pf.end()) << '\n';
    }

    return 0;
}