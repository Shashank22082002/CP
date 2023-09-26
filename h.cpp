#include <bits/stdc++.h>
using namespace std;
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cout.precision(numeric_limits<double>::max_digits10)
#define int long long
const int INF = 1E16;


vector<vector<int>> g;
vector<int> vis;
set<int> cycle;

void findCycle(int u, int p, vector<int> &st) {
    vis[u] = 1;
    st.push_back(u);
    for (auto &v: g[u]) {
        if (v == p) 
            continue;
        
        if (vis[v]) {
            if (!cycle.empty()) {
                continue;
            }
            for (int i = st.size() - 1; i >= 0; i--) {
                cycle.insert(st[i]);
                if (st[i] == v)
                    break;
            }
            return;
        }
        findCycle(v, u, st);
    }
    st.pop_back();
}

int findNode(int u, int p) {
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        if (cycle.find(v) != cycle.end()) {
            return v;
        }
        int node = findNode(v, u);
        if (node > 0)
            return node;
    }
    return -1;
}

void solve(){
    int n, a, b, u, v;
    cin >> n >> a >> b;
    g = vector<vector<int>> (n + 1);
    vis = vector<int> (n + 1);
    cycle.clear();
    for (int i = 0; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (a == b) {
        cout << "NO\n";
        return;
    }
    vector<int> st;
    findCycle(1, 0, st);
    // for (auto &it: cycle) {
    //     cout << it << " ";
    // }
    cout << endl;
    assert(!cycle.empty());
    if (cycle.find(b) != cycle.end()) {
        cout << "YES\n";
        return;
    }
    int node = findNode(b, 0);
    assert(node > 0);
    queue<int> q;
    vector<int> dis(n + 1, -1);
    dis[node] = 0;
    q.push(node);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (auto &ver: g[curr]) {
            if (dis[ver] == -1) {
                q.push(ver);
                dis[ver] = dis[curr] + 1;
            }
        }
    }
    if (dis[b] >= dis[a]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int32_t main ()
{
    FIO;
    int tt;
    cin>>tt;
    while(tt--)
        solve();
    return 0;
}