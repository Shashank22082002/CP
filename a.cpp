#include <bits/stdc++.h>
using namespace std;

#define int long long

using pii = pair<int, int>;
using PQState = tuple<int, int, int>;


const int MAXI = 1E12 + 169;


void solve() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    priority_queue<PQState, vector<PQState>, greater<>> pq;

    vector<vector<int>> dp(n + 1);
    vector<vector<int>> ans(n + 1);

    for (int i = 1; i <= n; ++i) {
        dp[i].assign(g[i].size(), MAXI);
        ans[i].assign(g[i].size(), MAXI);
    }

    dp[1][0] = 0;

    ans[1][0] = 0;
    pq.emplace(0, 0, 1);

    while (!pq.empty()) {
        auto [t, w, u] = pq.top(); 
        pq.pop();
        int d = g[u].size();
        int mod = t % d;

        if (dp[u][mod] < t) continue;

        int idx = mod;
        int v = g[u][idx];

        int d2 = g[v].size();
        int next_mod = (t + 1) % d2;
        if (dp[v][next_mod] > t + 1 || (dp[v][next_mod] == t + 1 && ans[v][next_mod] > w)) {
            dp[v][next_mod] = t + 1;
            ans[v][next_mod] = w;
            pq.emplace(t + 1, w, v);
        }

        int new_mod = (t + 1) % d;
        
        if (dp[u][new_mod] > t + 1 || (dp[u][new_mod] == t + 1 && ans[u][new_mod] > w + 1)) {
            dp[u][new_mod] = t + 1;
            ans[u][new_mod] = w + 1;
            pq.emplace(t + 1, w + 1, u);
        }
    }

    int best_time = MAXI, best_ans = MAXI;
    for (int mod = 0; mod < (int)g[n].size(); ++mod) {
        if (dp[n][mod] < best_time ||
            (dp[n][mod] == best_time && ans[n][mod] < best_ans)) {
            best_time = dp[n][mod];
            best_ans = ans[n][mod];
        }
    }

    cout << best_time << " " << best_ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}