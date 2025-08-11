#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

void dfs(int u, vector<int> &st, vector<bool> &vis, vector<vector<int>> &g) {
    vis[u] = 1;
    for (auto &v : g[u]) {
        if (vis[v])
            continue;
        dfs(v, st, vis, g);
    }
    st.push_back(u);
}

void dfs2(int u, vector<bool> &vis, vector<int> &curr_comp, vector<vector<int>> &rg) {
    curr_comp.push_back(u);
    vis[u] = 1;
    for (auto &v : rg[u]) {
        if (vis[v])
            continue;
        dfs2(v, vis, curr_comp, rg);
    } 
}

void solve() {
    int n, m, u, v;
    cin >> n >> m;
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    vector<bool> vis(n + 1);
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, st, vis, g);
        }
    }

    vis = vector<bool> (n + 1);
    vector<int> ans(n + 1);
    int comp_no = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (vis[st[i]])
            continue;
        comp_no++;
        vector<int> comp;
        dfs2(st[i], vis, comp, rg);
        for (auto &v : comp)
            ans[v] = comp_no;
    }
    cout << comp_no << "\n";
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}