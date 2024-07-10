#include <bits/stdc++.h>
using namespace std;
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cout.precision(numeric_limits<double>::max_digits10)
#define int long long
const int INF = 1E16;
const int MOD = 1E9 + 7;
const int N = 2E5;
int fact[N + 1];
void solve() {
    int n, k, x;
    cin >> n >> k;
    int oc = 0, ec = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x%2)
            oc++;
        else
            ec++;
    }
    if (k == 0) {
        if ((oc > 0) && (ec > 0)) {
            cout << 0 << endl;
        } else {
            cout << fact[n] << endl;
        }
    } else {
        if ((oc == ec) || (oc == ec + 1) || (ec == oc + 1)) {
            cout << (fact[oc] * fact[ec]) % MOD << endl;
        } else {
            cout << 0 << endl;
        }
    }
}

int32_t main ()
{
    FIO;
    int tt;
    cin>>tt;
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    while(tt--)
        solve();
    return 0;
}