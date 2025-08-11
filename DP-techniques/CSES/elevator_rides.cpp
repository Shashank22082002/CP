// https://cses.fi/problemset/task/1653
// Submask decomposition technique

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

void solve() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> w(n);
    for (int i = 0; i < n; ++i) cin >> w[i];

    // dp[mask] = pair{min rides, weight in last ride}
    const int ALL = 1 << n;
    vector<pair<int,long long>> dp(ALL, {n+1, 0});
    dp[0] = {1, 0}; // start with 1 ride with 0 weight

    for (int mask = 0; mask < ALL; ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) continue; // i already taken
            int nm = mask | (1 << i);
            auto cur = dp[mask];
            pair<int,long long> cand;
            if (cur.second + w[i] <= x) {
                // put person i in current ride
                cand = {cur.first, cur.second + w[i]};
            } else {
                // need a new ride for person i
                cand = {cur.first + 1, w[i]};
            }
            // take lexicographically smaller pair
            if (cand < dp[nm]) dp[nm] = cand;
        }
    }

    cout << dp[ALL - 1].first << "\n";
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