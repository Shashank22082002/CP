#include <bits/stdc++.h>
using namespace std;
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cout.precision(numeric_limits<double>::max_digits10)
#define int long long
const int INF = 1E16;
const int MOD = 1E9 + 7;
const int N = 2E5;
void solve() {
    int n, q, l, r;
    cin >> n >> q;
    vector<int> v(n), dp(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        dp[i + 1] = dp[i] + v[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << "\n";
    }
}
int32_t main () {
    FIO;
    int tt = 1;
    // cin>>tt;
    while(tt--)
        solve();
    return 0;
}