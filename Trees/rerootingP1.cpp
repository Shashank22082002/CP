/**
 * PROBLEM --> GIVEN A TREE T, FIND LONGEST PATH STARTING AT u FOR ALL NODES u.
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> f, h;

void dfs(int u, int p) {
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
    int n; // no of nodes.
    cin >> n;
    g = vector<vector<int>> (n+1);
    f = h = vector<int> (n+1);
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // compute fu(x) wrt some u, lets say 1...
    // h[u] = fu(u)
    dfs(1, 1);
    reroot(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << "Max length path starting at " << i << " is of len " << h[i] << endl;
    }

    return 0;
}