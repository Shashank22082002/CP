#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 1E9 + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>> (m + 1, vector<int> (n + 1)));

    // dp[i][j][k] -- number of arrays possible start at i, end at j, and populate k elements
    // dp[i][j][k] = dp[i + 1][j][k - 1] + dp[i - 1][j][k - 1]
    for (int i = 1; i <= m; i++) {
        if (i + 1 <= m)
            dp[i][i + 1][0] = 1;
        if (i > 1)
            dp[i][i - 1][0] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= n; k++) {
                dp[i][j][k] = dp[i + 1][j][k - 1] + dp[i - 1][j][k - 1];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}