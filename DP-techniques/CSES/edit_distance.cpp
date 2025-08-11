// https://cses.fi/problemset/task/2413/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
const int MOD = 1E9 + 7;
const int MAXN = 1E6 + 10;


void solve() {
    string s, t;
    cin >> s >> t;

    int n = s.size(), m = t.size();
    // dp[i][j] -- minimum number of steps to convert s[1 .. i] to t[1 .. j]
    vector<vector<int>> dp(n + 1, vector<int> (m + 1, MAXN));
    vector<int> prev(m + 1, MAXN), curr(m + 1, MAXN);
    prev[0] = 0;

    for (int j = 1; j <= m; j++)
        prev[j] = j;

     for (int i = 1; i <= n; i++) {
        curr.assign(m + 1, MAXN);
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                curr[j] = min({prev[j - 1], 
                                1 + curr[j - 1], 
                                1 + prev[j]});
            } else {
                curr[j] = min({1 + prev[j - 1], 
                                1 + curr[j - 1], 
                                1 + prev[j]});
            }
        }
        prev = curr;
    }
    cout << curr[m] << "\n";
}


int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    solve();
    return 0;
}