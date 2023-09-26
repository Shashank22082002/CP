/**
 * Maximum white subtree --> https://codeforces.com/problemset/problem/1324/F
 * modified verison of P1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9+7;
int n;
vector<vector<int>> g;
vector<int> c, rd, md; // rooted diff, max diff

void dfs (int u, int p) {
    for (auto v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        rd[u] += max(0, rd[v]);
    }
}

void reroot (int u, int p) {
    md[u] = rd[u];
    for (auto &v : g[u]) {
        // rerooting from u -- v
        if (v == p) continue;
        int init_u = rd[u], init_v = rd[v];
        if (rd[v] >= 0) {
            rd[u] -= rd[v];
            rd[v] += max(0, rd[u]);
        } else {
            rd[v] += max(0, rd[u]);
        }
        reroot(v, u);
        rd[u] = init_u, rd[v] = init_v;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    c = vector<int> (n+1);
    md = vector<int> (n+1, -INF);
    g = vector<vector<int>> (n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        if(c[i] == 0)
            c[i]--;
    }
    rd = c;
    int u, v;
    for (int i = 0; i < n-1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    reroot(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << md[i] << " ";
    }
    cout << endl;

    return 0;
}