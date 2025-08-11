#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
// int dp[501][501];

// int f(int a, int b) {
//     if (a == b)
//         return 0;

//     if (dp[a][b] != -1)
//         return dp[a][b];

//     int steps = 300000;
//     for (int i = 1; i < a; i++) {
//         steps = min(steps, 1 + f(i, b) + f(a - i, b));
//     }
//     for (int i = 1; i < b; i++) {
//         steps = min(steps, 1 + f(a, i) + f(a, b - i));
//     }

//     return dp[a][b] = steps;
// }


void solve() {
    int a, b;
    cin >> a >> b;
    // dp[i][j] -- min steps to convert a rectangle of i * j size into squares
    // dp[i][j] = dp[1][j] + dp[i - 1][j], dp[2][j] + dp[i - 2][j] ...
    // dp[i][j] = dp[i][1] + dp[i][j - 1], dp[i][2] + dp[i][j - 2], dp[i][3] + dp[i][j - 3] ..

    vector<vector<int>> dp(a + 1, vector<int> (b + 1, 300000));
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j)
                dp[i][j] = 0;
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i - k][j]);
            }
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j - k]);
            }
        }
    }
    cout << dp[a][b] << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // memset(dp, -1, sizeof dp);
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}