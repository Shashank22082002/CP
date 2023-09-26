// cses longest flight route
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> topo, vis, dp;
int n, m;

void dfs(int u) {
    vis[u] = 1;
    for(auto &v: g[u]) {
        if(!vis[v])
            dfs(v);
    }
    topo.push_back(u);
}

int path(int u) {
    if(dp[u] != -1) {
        return dp[u];
    }
    if(u == n) {
        return dp[u] = 1;
    }
    // dp[u] -- longest path from u -- n
    int ways = 0;
    for (auto &v: g[u]) {
        ways += path(v);
    }
    return dp[u] = ways;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    int u, v;
    set<pair<int, int>> edges;
    g = vector<vector<int>> (n+1);
    vis = vector<int> (n+1);
    dp = vector<int> (n+1, -1);
    for(int i = 0; i < m; i++) {
        cin >> u >> v;
        edges.insert({u, v});
    }
    for (auto &edge: edges) {
        u = edge.first;
        v = edge.second;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if(!vis[i])
            dfs(i);
    }
    reverse(topo.begin(), topo.end());
    // apply dp in topo-order
    for(auto &v: topo) {
        path(v);
    }
    
    
    cout << path(1) << endl;

    return 0;
}
