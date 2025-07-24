#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1E12;

using PQState = tuple<int, int, int>;
// time, wait_time, node

void solve() {
    int n, m, u, v;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> dp(n + 1);
    vector<vector<int>> wt(n + 1);
    for (int i = 1; i <= n; i++) {
        dp[i] = vector<int> (g[i].size(), INF);
        wt[i] = vector<int> (g[i].size(), INF);
    }
    // dp[i][e] == min time to reach state node i, edge e, where e denotes the edge from which immediate movement will happen
    priority_queue<PQState> pq;
    pq.emplace(0, 0, 1);
    dp[1][0] = 0;
    while (!pq.empty()) {
        auto [t, w, u] = pq.top(); pq.pop();

        int sz = g[u].size();
        assert(sz > 0);
        if (dp[u][t % sz] < t)
            continue;
            
        int edge = (t + 1) % sz;

        // wait
        if (dp[u][edge] > t + 1 || (dp[u][edge] == t + 1 && wt[u][edge] > w + 1)) {
            dp[u][edge] = t + 1;
            wt[u][edge] = w + 1;
            pq.emplace(t + 1, w + 1, u);
        }

        // move
        int v = g[u][t % sz];
        int edge_v = (t + 1) % g[v].size();
        if (dp[v][edge_v] > (t + 1) || (dp[v][edge_v] == t + 1 && wt[v][edge_v] > w)) {
            dp[v][edge_v] = (t + 1);
            wt[v][edge_v] = w;
            pq.emplace(t + 1, w, v);
        }
    }

    int ans = INF, wait = INF;
    for (int i = 0; i < g[n].size(); i++) {
        if (dp[n][i] < ans) {
            ans = dp[n][i];
            wait = wt[n][i];
        }
    }
    cout << ans << " " << wait << "\n";
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}