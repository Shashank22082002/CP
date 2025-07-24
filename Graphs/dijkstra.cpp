#include <bits/stdc++.h>
using namespace std;
 
#define int long long
const int INF = 1E15;
 
void solve() {
    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dis(n + 1, INF);
    dis[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [r, u] = pq.top(); pq.pop();
        if (r > dis[u])
            continue;
        assert(r == dis[u]);
        for (auto [v, d] : g[u]) {
            if (dis[v] > r + d) {
                dis[v] = r + d;
                pq.emplace(dis[v], v);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
}
 
int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}