// https://atcoder.jp/contests/abc202/tasks/abc202_e

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}
const int mod = 1e9+7;
#define all(v) v.begin(), v.end()

vector<vector<int>> g;
vector<vector<int>> d;
vector<int> in, out;
int tim = 0;

void dfs(int u, int dep = 0) {
    in[u] = tim++;
    d[dep].push_back(in[u]);
    for (auto &v: g[u]) {
        dfs(v, dep + 1);
    }
    out[u] = tim;
}

void solve() {
    int n, q;
    cin >> n;
    g = d = vector<vector<int>> (n + 1);
    in = out = vector<int> (n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    dfs(1);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, D;
        cin >> u >> D;
        cout << lower_bound(all(d[D]), out[u]) - lower_bound(all(d[D]), in[u]) << endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    int t = 1;
    // cin >> t;
    for (int _t = 0; _t < t; _t++) {
        solve();
    }
}