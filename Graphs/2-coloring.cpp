#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> g;

bool dfs(int u, vector<int> &color) {
    bool poss = 1;
    for (auto &v : g[u]) {
        if (color[v] == -1) {
            color[v] = 1 - color[u];
            poss = poss & dfs(v, color);
        } else if (color[v] != (1 - color[u])) {
            poss = 0;
        }
    }
    return poss;
}

void solve() {
    // 2 coloring problem
    // https://cses.fi/problemset/task/1668
    
    int n, m, u, v;
    cin >> n >> m;
    g = vector<vector<int>> (n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            if (!dfs(i, color)) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << color[i] + 1 << " ";
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}