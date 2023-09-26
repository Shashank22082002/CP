// easy tree dp
// independent set problem
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
 
const int INF = 2e9 + 7;
const int MOD = 1E9 + 7;

vector<vector<int>> g;
vector<vector<int>> dp;
int dfs(int u, int p, bool c) {
    if(dp[u][c] != -1) {
        return dp[u][c];
    }
    int ans = 1;
    for(auto &v: g[u]) {
        if(v == p)
            continue;
        int lans = dfs(v, u, !c);
        if(c == 0) {
            lans += dfs(v, u, c);
        }
        ans *= (lans % MOD);
        ans %= MOD;                
    }
    return dp[u][c] = ans;
}

void solve() {
    int n, u, v;
    cin >> n;
    g = vector<vector<int>> (n+1);
    dp = vector<vector<int>> (n+1, vector<int> (2, -1));
    for(int i = 0; i < n-1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout << (dfs(1, 0, 0) + dfs(1, 0, 1)) % MOD << endl;
}
 
intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    for(int _t = 0; _t < t; _t++)
        solve();
    return 0;
}