#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
const int MOD = 1E9 + 7;
const int MAXN = 1E6 + 10;

int dp[MAXN][2];

void solve() {
    int n;
    cin >> n;

    // dp[i][linked] -- number of ways of building up from i to N given i - 1 tiles were in pairs
    // dp[i][not linked]
    // dp[i][0] = 4 * dp[i + 1][0] + dp[i + 1][1]
    // dp[i][1] = dp[i + 1][0] + 2 * dp[i + 1][1]
    // then reverse this DP .. not logically but codewise storing in array

    if (n == 1) {
        cout << 2 << endl;
        return;
    }

    cout << (dp[n][0] + dp[n][1]) % MOD << "\n";
}


int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    cin >> T;
    memset(dp, 0, sizeof dp);
    dp[2][0] = 5;
    dp[2][1] = 3;
    for (int i = 3; i < MAXN; i++) {
        dp[i][0] = (4 * dp[i - 1][0] + dp[i - 1][1]) % MOD;
        dp[i][1] = (dp[i - 1][0] + 2 * dp[i - 1][1]) % MOD;
    }
    while (T--) {
        solve();
    }
    return 0;
}