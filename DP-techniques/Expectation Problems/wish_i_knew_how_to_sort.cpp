// https://codeforces.com/contest/1753/problem/C

#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

const int MOD = 998244353;

int binpow(int a, int b) {
    a %= MOD;
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int g = count(v.begin(), v.end(), 0ll);
    int x = count(v.begin(), v.begin() + g, 1ll);
    int exp = 0;
    int num = (n * (n - 1) / 2) % MOD; 
    for(int j = x; j > 0; j--) {
        exp = (exp + binpow(j * j, MOD - 2)) % MOD;
    }
    cout << exp * num % MOD << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++) 
        solve();
    return 0;
}