#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
 
void solve() {
    int n, e, s, r;
    cin >> n;
    vector<tuple<int, int, int>> vp;
    for (int i = 1; i <= n; i++) {
        cin >> s >> e >> r;
        vp.emplace_back(e, s, r);
    }
    vp.emplace_back(0, 0, 0);
    sort(vp.begin(), vp.end());
    vector<int> dp(n + 1);
    int maxi = 0;
    for (int i = 1; i <= n; i++) {
        auto [e, s, r] = vp[i];
        tuple<int, int, int> p = {s, 0ll, 0ll};
        // find the interval whose end is just after vp[i].second
        auto it = lower_bound(all(vp), p);
        auto idx = it - vp.begin() - 1;
        dp[i] = max(dp[i - 1], dp[idx] + r);
        maxi = max(maxi, dp[i]);
    }
    cout << maxi << "\n";
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