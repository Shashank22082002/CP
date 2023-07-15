// lca + euler's tour of tree great problem
// https://codeforces.com/contest/1774/problem/E
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, d, x, y;
const int lg = 17;
vector<vector<int>> g, f;
vector<int> p, dis;

void dfs(int u) {
    for (auto &v: g[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        dis[v] = dis[u] + 1;
        dfs(v);
    }
}

void init() {
    p = dis = vector<int> (n+1);
    dfs(x); // root x
    p[x] = x;
    f[0] = p; // 2^0th parent
    for (int i = 0; i < lg; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[i+1][j] = f[i][f[i][j]]; // 2^(i+1)th parent;
        }
    }
}

int KthAncestor(int u, int k) {
    for (int i = lg; i >= 0; --i) {
        if(k >> i & 1) u = f[i][u];
    }
    return u;
}

int LCA(int u, int v) {
    if (dis[u] > dis[v])
        u = KthAncestor(u, dis[u] - dis[v]);
    else
        v = KthAncestor(v, dis[v] - dis[u]);
    if (u == v) return u;
    for (int i = lg; i >= 0; --i) {
        if(f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }
    return f[0][u];
}

int distance(int u, int v) {
    return dis[u] + dis[v] - 2*dis[LCA(u, v)];
}


int bfs(set<int> &st) {
    queue<int> q;
    vector<int> vis(n+1), deg(n+1);
    for(int i = 1; i <= n; i++) {
        deg[i] += g[i].size();
    }
    for(int i = 1; i <= n; i++) {
        if(g[i].size() == 1 && i != x){
            q.push(i);
            vis[i] = 1;
        }
    }
    int ct = 0;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        if(st.find(node) != st.end())
            continue;
        for(auto &v: g[node]) {
            if(vis[v]) continue;
            deg[v]--;
            if(deg[v] == 1) {
                q.push(v);
                vis[v] = 1;
            }
            ct++;
        }
    }
    return 2*(n-1-ct);
}
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    cin >> n >> d;
    x = 1;
    g = vector<vector<int>> (n+1);
    f = vector<vector<int>> (lg+1, vector<int> (n+1));
    int u, v, m1, m2;
    for(int i = 0; i < n-1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    set<int> a, b;
    cin >> m1;
    for(int i = 0; i < m1; i++) {
        cin >> u;
        a.insert(u);
    }
    cin >> m2;
    for(int i = 0; i < m2; i++) {
        cin >> v;
        b.insert(v);
    }
    a.insert(x);
    b.insert(x);
    init();
    for(auto &u: a) {
        
        b.insert(KthAncestor(u, d));
    }
    
    for(auto &v: b) {
        
        a.insert(KthAncestor(v, d));
    }
    // for(auto &it: a) {cout << it << " ";}
    // cout << endl;
    // for(auto &it: b) {cout << it << " ";}
    // cout << endl;
    // cout << bfs(b) << endl;
    cout << bfs(a) + bfs(b) << '\n';
    return 0;
}