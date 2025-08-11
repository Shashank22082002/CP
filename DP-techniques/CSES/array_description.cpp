 #include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
const int MOD = 1E9 + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // dp[i][x] == number of arrays of length i, that end at x
    // dp[0][a[0]] = 1, if a[0] != 0
    // dp[0][p] = 1, if a[0] == 0 for p in [1, m]

    // dp[i][x] = 0 if a[i] != x and a[i] != 0
    // dp[i][x] = dp[i - 1][x - 1] + dp[i - 1][x] + dp[i - 1][x + 1] if a[i] == 0 or a[i] == x

    vector<vector<int>> dp(n + 1, vector<int> (m + 2));
    if (v[0] != 0)
        dp[0][v[0]] = 1;
    else 
        for (int i = 1; i <= m; i++) dp[0][i] = 1;

    for (int i = 1; i < n; i++) {
        for (int x = 1; x <= m; x++) {
            if (v[i] == 0 || v[i] == x) {
                dp[i][x] = ((x > 1 ? dp[i - 1][x - 1] : 0) + (x < m ? dp[i - 1][x + 1] : 0) + dp[i - 1][x]) % MOD;
            }
        }
    }

    int ans = 0;

    for (int x = 1; x <= m; x++)
        ans = (ans + dp[n - 1][x]) % MOD;
    
    cout << ans << "\n";
        

    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}