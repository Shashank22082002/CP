#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> g;

bool dfs(int u, int p, vector<bool> &vis, vector<int> &path, vector<int> &cycle) {
    path.push_back(u);
    vis[u] = 1;
    for (auto &v : g[u]) {
        if (v == p)
            continue;
        if (vis[v]) {
            cycle.push_back(v);
            while (true) {
                auto last = path.back();
                path.pop_back();
                cycle.push_back(last);
                if (last == v)
                    break;
            }
            return true;
        }
        if (dfs(v, u, vis, path, cycle)) {
            return true; 
        }
    }
    path.pop_back();
    return false;
}

void solve() {
    // cycle detection in graph
    // https://cses.fi/problemset/task/1669
    int n, m, u, v;
    cin >> n >> m;
    g = vector<vector<int>> (n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<bool> vis(n + 1);
    vector<int> path, cycle;
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && dfs(i, 0, vis, path, cycle)) {
            cout << cycle.size() << "\n";
            for (auto &it : cycle) cout << it << " ";
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}