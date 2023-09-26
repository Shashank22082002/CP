// https://leetcode.com/contest/biweekly-contest-113/problems/minimum-edge-reversals-so-every-node-is-reachable/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> f, h;
    vector<vector<int>> g;
    set<pair<int, int>> edg;
    int dfs(int u, int p) {
        if (f[u] != -1) {
            return f[u];
        }
        int ans = 0;
        for (auto &v: g[u]) {
            if(v == p)
                continue;
            ans += edg.count({v, u});
            ans += dfs(v, u);
        }
        return f[u] = ans;
    }
    void reroot(int u, int p) {
        h[u] = f[u];
        for (auto &v: g[u]) {
            if (v == p)
                continue;
            int init_fu = f[u], init_fv = f[v];
            int ext = h[u] - f[v];
            if (edg.find({u, v}) != edg.end()) {
                ext++;
            } else {
                ext--;
            }
            f[v] += ext;
            reroot(v, u);
            f[u] = init_fu, f[v] = init_fv;
        }
    }
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        f = h = vector<int> (n, -1);
        g = vector<vector<int>> (n);
        edg.clear();
        
        for (auto &it: edges) {
            int u = it[0], v = it[1];
            g[u].push_back(v);
            g[v].push_back(u);
            edg.insert({u, v});
        }
        dfs(0, -1);
        reroot(0, -1);
        return h;
    }
};