// distinct colors using small to large merging technique

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 1e9+7;

vector<vector<int>> g;
int n;
vector<set<int>> vs;
vector<int> sno, ans; // sno -- set number, index of vs where set for a vertex is present

void merge(int u, int v) {
    int nu = sno[u];
    int nv = sno[v];
    if (vs[nu].size() > vs[nv].size()) {
        swap(u, v);
        swap(nu, nv);
    }
    for (auto &it: vs[nu]) {
        vs[nv].insert(it);
    }
    sno[u] = nv;
}

void dfs(int u, int p) {
    for (auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        merge(u, v);
    }
    ans[u] = vs[sno[u]].size();
}

void solve() {
    cin >> n;
    int u, v;
    vs = vector<set<int>> (n + 1);
    g = vector<vector<int>> (n + 1);
    sno = ans = vector<int> (n + 1);
    int col;
    for (int i = 1; i <= n; i++) {
        cin >> col;
        vs[i].insert(col);
        sno[i] = i;
    }
    for (int i = 1; i < n; i++ ){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    
    solve();
}