#include <bits/stdc++.h>
using namespace std;
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cout.precision(numeric_limits<double>::max_digits10)
// #define int long long
const int INF = 1E16;
const int N = 2E5;

vector<vector<int>> g;
vector<int> p;

vector<int> num;
vector<int> ans;
vector<int> h;
int no;

void giveNum(int u) {
    for (auto &v: g[u]) {
        giveNum(v);
    }
    num[u] = ++no;
}

void dfs_heights(int u) {
    for (auto &v: g[u]) {
        dfs_heights(v);
        h[u] = max(h[u], h[v] + 1);
    }
    h[u] = max(h[u], 1);
}

void dfs(int u) {
    int mini = N, val = 0;
    for (auto &v: g[u]) {
        dfs(v);
        mini = min(mini, num[v]);
        val += ans[v];
    }
    if (g[u].size() == 1) {
        val++;
    }
    num[u] = mini;
    ans[u] = max(val, h[u]);
}

void solve() {
    int n;
    cin >> n;
    h = ans = p = num = vector<int> (n + 1);
    g = vector<vector<int>> (n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }
    giveNum(1);
    dfs_heights(1);
    dfs(1);
    cout << ans[1] << endl;
}

int32_t main ()
{
    FIO;
    int tt = 1;
    // cin>>tt;
    while(tt--)
        solve();
    return 0;
}