// https://cses.fi/problemset/task/1137

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>> g;
vector<int> in, out, val, subtree_sum;
int timer;
template <typename T> struct Fenwick {
    vector<T> a;
    int n;
    Fenwick() : a(), n(0) {}
    Fenwick(int _n) {
        n = _n;
        a = vector<T> (n, T());
    }
    void clear() {
        a = vector<T> (n, T());
    }
    void add(int p, T x) {
        for(; p < n; p += (p & (-p)))
            a[p] += x;
    }
    T get(int r) {
        T res = T();
        for(; r > 0; r -= (r & (-r)))
            res += a[r];
        return res;
    } 
    T getSum(int l, int r) {
        return get(r) - get(l - 1);
    }
};

void dfs(int u, int p) {
    in[u] = ++timer;
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        dfs(v, u);
    }
    out[u] = timer;
}


int main() {
    int n, q, u, v, type, x, s;
    cin >> n >> q;
    in = out = val = vector<int> (n + 1);
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    g = vector<vector<int>> (n + 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    Fenwick<ll> f(n + 1);
    for (int i = 1; i <= n; i++) {
        f.add(in[i], val[i]);
        // cout << i << " " << in[i] << " " << out[i] << endl;
    }
    for (int i = 0; i < q; i++) {
        cin >> type;
        if (type == 1) {
            cin >> s >> x;
            // cout << x << " " << val[s] << " " << s << endl;
            f.add(in[s], x - val[s]);
            val[s] = x;
        } else if (type == 2){
            cin >> s;
            cout << f.getSum(in[s], out[s]) << endl;
        } else {
            assert(false);
        }
    }
    return 0;
}