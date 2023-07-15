// again same AS P1 !!!
// https://codeforces.com/contest/1805/problem/D


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


#define showVVI(arr)           \
{                              \
    for (auto &vvv : arr)      \
    {                          \
        for (auto &xxxx : vvv) \
            csp(xxxx);         \
        cout << endl;          \
    }                          \
}

const int INF = 1e18 + 7;
const int N = 1e6;

int n;
vector<vector<int>> g;
vector<int> f, h;

void dfs(int u, int p) {
    for (auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        f[u] = max(f[u], f[v] + 1);
    }
}

void reroot(int u, int p) {
    h[u] = f[u];
    int argmax = -1, md = 0;
    for (auto &v: g[u]) {
        if (h[u] == 1 + f[v])
            argmax = v;
    }
    for (auto &v: g[u]) {
        if (v == p) continue;
        // reroot from u -- v
        int init_u = f[u], init_v = f[v];
        if(argmax == v) {
            f[u] = 0;
            for (auto &ch: g[u]) {
                if (ch == v) continue;
                f[u] = max(f[u], 1 + f[ch]);
            }
        }
        f[v] = max(f[v], 1 + f[u]);
        reroot(v, u);
        f[u] = init_u, f[v] = init_v;
    }
}


void solve() {
    // maximum distance of every vertex from any node
    // standard rerooting problem
    cin >> n;
    int u, v;
    g = vector<vector<int>> (n+1);
    h = f = vector<int> (n+1);
    for (int i = 0; i < n-1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    reroot(1, 0);
    // show(h);
    multiset<int> st;
    for (int i = 1; i <= n; i++)
        st.insert(h[i]);
    int ct = 0;
    for(int k = 1; k <= n; k++) {
        while(st.find(k-1) != st.end()) {
            st.erase(st.find(k-1));
            ct++;
        }
        cout << ct + (st.size() != 0) << " ";
    }
    cout << endl;
}

intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(numeric_limits<double>::max_digits10);

    int t = 1;
    // cin >> t;
    for(int i = 0; i < t; i++) solve();
    return 0;
}
