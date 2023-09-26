// awesome problem on directed cyclic graph..
// https://codeforces.com/contest/1787/problem/D
#include <bits/stdc++.h>
using namespace std;
#define intt int32_t
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
typedef long long ll;
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}

#define showVpi(arr)                     \
{                                        \
    for(auto &it : arr)                  \
    cout<<it.first<<" "<<it.second<<endl;\
}    

const int MOD = 998244353;
const int N = 2E5+1;
const int INF = 1E18;

vector<vector<int>> g, rg;
vector<int> cycle, vis;
vector<int> reachable;
int n;

void dfs(int u) {
    vis[u] = 1;
    for(auto &v: rg[u]) {
        if(vis[v] == 1 || v == n+1) {
            vis[u] = 2;
            return;
        }
        if(vis[v] == 0)
            dfs(v);
        // cout << u << " " << v << endl;
        reachable[u] += (1 + reachable[v]);
    }
    vis[u] = 2;
}

void solve() {
    cin >> n;
    vector<int> v(n);
    vis = reachable = vector<int> (n+2);
    cycle = vector<int> (n+2, -1);
    g = vector<vector<int>> (n+2);
    rg = vector<vector<int>> (n+2);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        int u = i+1;
        int s = i+1+v[i];
        if(s > n || s < 1)
            s = n+1;
        g[u].push_back(s);
        rg[s].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    // show(reachable);
    // find vertex forming a cycle..
    for(int i = 1; i <= n; i++) {
        if(cycle[i] == -1) {
            int v = g[i][0];
            set<int> st;
            st.insert(i);
            while(true) {
                if(v == n+1) {
                    for(auto &it: st) {
                        cycle[it] = 0;
                    }
                    st.clear();
                    break;
                }
                if(st.find(v) != st.end()) {
                    for(auto &it: st) {
                        cycle[it] = 1;
                    }
                    st.clear();
                    break;
                }
                if(cycle[v] != -1) {
                    for(auto &it: st) {
                        cycle[it] = cycle[v];
                    }
                    st.clear();
                    break;
                }
                st.insert(v);
                v = g[v][0];
            }
        }
    }
    int ct = 0;
    for (int i = 1; i <= n; i++) {
        if(cycle[i] == 1)
            ct++;
    }
    // check if 1 forms a cycle
    if(cycle[1]) {
        // find the path length
        set<int> st;
        st.insert(1);
        int v = g[1][0];
        while(st.find(v) == st.end()) {
            st.insert(v);
            v = g[v][0];
        }
        cout << st.size() * (2*n + 1 - ct) << endl;
    } else {
        int ans = 0;
        int v = 1;
        set<int> st;
        while(v != n+1) {
            // do not go to any cyclic vertex or u such that v is reachable from u
            st.insert(v);
            // cout << v << " " << reachable[v] << endl;
            ans += (2*n - reachable[v] - ct);
            v = g[v][0];
        }
        ans += (2*n+1)*(n - st.size());
        // int x = (st.size() * (st.size() - 1))/2;
        cout << ans << endl;
    }
}

intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(numeric_limits<double>::max_digits10);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++) solve();
    return 0;
}

