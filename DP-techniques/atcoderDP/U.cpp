// U - Grouping problem
// idea -- form groups one by one

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1E18L + 5;

vector<vector<int>> in;
vector<int> dp;
vector<int> group_score;

void solve() {
    int n;
    cin >> n;
    in = vector<vector<int>> (n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> in[i][j];
        }
    }

    group_score = vector<int> (1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                for (int j = i + 1; j < n; j++) {
                    if (mask >> j & 1) {
                        group_score[mask] += in[i][j];
                    }
                }
            }
        }
    }

    // dp[mask] == best answer possible by grouping mask
    dp = vector<int> (1 << n, -INF);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> not_taken;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) 
                continue;
            not_taken.push_back(i);
        }
        // try forming a group out of not takens
        int m = not_taken.size();
        for (int grp = 0; grp < (1 << m); grp++) {
            int group = 0;
            for (int i = 0; i < m; i++) {
                if (grp >> i & 1) {
                    group = group ^ (1 << not_taken[i]);
                }
            }
            dp[mask ^ group] = max(dp[mask ^ group], dp[mask] + group_score[group]);
        }
    }
    cout << dp[(1 << n) - 1] << endl;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
    return 0; 
}