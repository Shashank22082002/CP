#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1E15;

void solve() {
    int n, m, u, v, w, q;
    cin >> n >> m >> q;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<vector<int>> dp(n + 1, vector<int> (n + 1, INF));

    for (int i = 1; i <= n; i++) dp[i][i] = 0;
    for (int u = 1; u <= n; u++) {
        for (auto &[v, w] : g[u]) {
            dp[u][v] = min(dp[u][v], w);
        }
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] < INF && dp[k][j] < INF)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (dp[a][b] >= INF)
            cout << -1 << "\n";
        else
            cout << dp[a][b] << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}