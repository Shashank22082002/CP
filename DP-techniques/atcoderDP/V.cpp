#include <bits/stdc++.h>
using namespace std;

#define int long long
int MOD;
int phiMOD;
vector<vector<int>> g;
vector<int> f, h;

 
int phi(int n) {
    // Initialize result as n
    int result = n;
  
    // Consider all prime factors of n
    // and subtract their multiples
    // from result
    for(int p = 2; p * p <= n; ++p)
    {
         
        // Check if p is a prime factor.
        if (n % p == 0)
        {
             
            // If yes, then update n and result
            while (n % p == 0)
                n /= p;
                 
            result -= result / p;
        }
    }
  
    // If n has a prime factor greater than sqrt(n)
    // (There can be at-most one such prime factor)
    if (n > 1)
        result -= result / n;
         
    return result;
}
  

int inv(int a) {
    // inverse of a modulo MOD
    assert(a != 0);
    int res = 1, b = phiMOD - 1;
    while(b) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int divide(int a, int b) {
    if(a == 0)
        return 0;
    int g = __gcd(a, b);
    a /= g;
    b /= g;
    return (a * inv(b)) % MOD;
}

void dfs(int u, int p) {
    int ans = 1;
    for (auto &v: g[u]) {
        if (p == v) continue;
        dfs(v, u);
        ans = (ans * f[v]) % MOD;
    }
    f[u] = (1 + ans) % MOD;
}



void reroot(int u, int p) {
    h[u] = f[u];
    for (auto &v: g[u]) {
        if (v == p) continue;
        // reroot from u -- v
        int init_u = f[u], init_v = f[v];
        f[u] = (divide(f[u] - 1, f[v]) + 1) % MOD;
        // f[u] = ((f[u] - 1) / f[v]) + 1;
        f[v] = ((f[v] - 1) * f[u] + 1) % MOD;
        reroot(v, u);
        f[u] = init_u;
        f[v] = init_v;
    }
}



void solve() {
    int n, u, v;
    cin >> n >> MOD;
    phiMOD = phi(MOD);
    g = vector<vector<int>> (n + 1);
    f = vector<int> (n + 1, 1); // gives the local subtree score -- f[v] number of ways to color subtree rooted at v
    h = vector<int> (n + 1);
    for (int i = 0; i < n-1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    reroot(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << (h[i] - 1 + MOD) % MOD << endl;
    }
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
    return 0; 
}