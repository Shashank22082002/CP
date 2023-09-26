#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 3069;
ll fact[N + 1], invfact[N + 1];
int MOD;

ll binpow(ll a, int b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    fact[0] = 1;
    int n;
    cin >> n >> MOD;
    for (int i = 1; i <= N; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
    invfact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
    auto NCR = [&](int n, int r) {
        if (n == 0 || n < r) 
            return 0ll;
        ll res = 1;
        res *= (fact[n] * invfact[r]) % MOD;
        res *= invfact[n - r];
        return res % MOD;
    };
    ll sum = 0;
    int t = (n + 1) / 2;
    for (int x = 0; x < t; x++ ) {
        // ending peg at x;
        int m = n - (x + 1); // must remove
        int o = max(x - 1, 0);
        int l = n/2 + x - (n + 1)/2 + 1;
        for (int s = 0; s <= o; ++s) {
            // intermediate pegs that can be removed = s
            // last peg = n/2 + x - (n+1)/2 + 1
            cout << m << " " << o << " " << l << endl;
            sum += (NCR(o, s) * fact[m + s - 1] % MOD) * l % MOD;
            sum %= MOD;
        }
    }
    cout << sum * n % MOD << endl;
    return 0; 
}