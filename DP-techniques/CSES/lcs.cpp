
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
const int MOD = 1E9 + 7;
const int MAXN = 1E6 + 10;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a (n), b (m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    // dp[i][j] -- max length of subsequence in the range a[1 .. i] and b[1 .. j]
    vector<vector<int>> dp(n + 1, vector<int> (m + 1));
    map<pair<int, int>, pair<int, int>> pars;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int best = dp[i][j];
            pair<int, int> parent = {-1, -1};
            if (a[i - 1] == b[j - 1] && dp[i - 1][j - 1] + 1 > best) {
                best = dp[i - 1][j - 1] + 1;
                parent = {i - 1, j - 1};   
            }
            if (dp[i][j - 1] > best) {
                best = dp[i][j - 1];
                parent = {i, j - 1};
            }
            if (dp[i - 1][j] > best) {
                best = dp[i - 1][j];
                parent = {i - 1, j};
            }
            dp[i][j] = best;
            pars[{i, j}] = parent;
        }
    }

    cout << dp[n][m] << "\n";

    vector<int> lcs;
    pair<int, int> curr_state = {n, m};
    while (true) {
        if (curr_state.first <= 0 || curr_state.second <= 0) {
            break;
        }
        auto [x, y] = curr_state;
        // cout << x << " " << y << endl;
        if (a[x - 1] == b[y - 1]) {
            lcs.push_back(a[x - 1]);
        }
        curr_state = pars[curr_state];
    }
    reverse(all(lcs));
    for (auto num : lcs)
        cout << num << " ";
    cout << "\n";

}


int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    solve();
    return 0;
}