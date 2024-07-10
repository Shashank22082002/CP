// https://codedrills.io/contests/icpc-algoqueen-2024---practice-contest-1/problems/d-tree
// Properties in subtree using euler tour
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(v) v.begin(), v.end()
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

const int N = 2E5 + 5;
const int INF = 1E9;

// f[d] contains dp values of vertices at depth d
// in[d] contains intimes of vertices at depth d
// out[d] contains outtimes of vertices at depth d

vector<vector<int>> g, f, in, out;
vector<int> a, d, dp, IT, OT;

int n, q, tim;

void dfs(int u, int p = 0) {
    dp[u] += a[u];
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        d[v] = d[u] + 1;
        dfs(v, u);
        dp[u] += dp[v];
    }
}

void euler_tour(int u, int p = 0) {
    in[d[u]].push_back(tim++);
    IT[u] = tim;
    f[d[u]].push_back(dp[u]);
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        euler_tour(v, u);
    }
    out[d[u]].push_back(tim);
    OT[u] = tim;
}

int query(int u, int d) {
    auto &iv = in[d + 1];
    auto &ov = out[d + 1];
    auto itl = lower_bound(iv.begin(), iv.end(), IT[u]); //  2 3
    auto itr = upper_bound(ov.begin(), ov.end(), OT[u]); // 3 4
    if (itl == iv.end() || *itl > OT[u]) {
        return dp[u];
    }
    assert(itr != ov.begin());
    --itr;
    int l = itl - iv.begin();
    int r = itr - ov.begin();
    if (l == 0)
        return dp[u] - f[d + 1][r];
    else
        return dp[u] - f[d + 1][r] + f[d + 1][l - 1];
}


void solve() {
    int u, v, x, D;
    cin >> n >> q;
    f = g = in = out = vector<vector<int>> (n + 1);
    OT = IT = a = d = dp = vector<int> (n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    euler_tour(1);
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (auto &it: f[i]) {
            sum += it;
            it = sum;
        }
    }
    for (int i = 0; i < q; i++) {
        cin >> x >> D;
        cout << query(x, D) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    // RunLinearSieve();
    cin >> t;
    for (int _t = 0; _t < t; _t++) {
        solve();
    }
    return 0;
}