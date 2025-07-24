// https://atcoder.jp/contests/tokiomarine2020/tasks/tokiomarine2020_d

// MEET IN THE MIDDLE TECHNIQUE PROBLEM
// DP for nodes whatever is possible
// Recursion for rest.. and take help from DP

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = (1 << 18) + 100;
const int TOPN = (1 << 9) + 1;
const int MAXW = 100010;
int W[MAXN], V[MAXN];
int dp[TOPN][MAXW];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q, v, l;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> V[i] >> W[i];
    }

    for (int i = 1; i <= min(TOPN - 1, n); i++) {
        for (int w = 0; w < MAXW; w++) {
            // dp[i][w] -- denotes maximum value I can get from nodes[1..i]
            if (W[i] > w) {
                dp[i][w] = dp[i/2][w];
            } else {
                dp[i][w] = max(dp[i/2][w], dp[i/2][w - W[i]] + V[i]);
            }
        }
    }

    cin >> q;
    while (q--) {
        cin >> v >> l;
        if (v < TOPN) {
            cout << dp[v][l] << "\n";
            continue;
        }
        vector<int> rest;
        while (v >= TOPN) {
            rest.push_back(v);
            v /= 2;
        }

        // GENERATE ALL POSSIBLE COMBINATIONS FOR REST
        int len = rest.size();
        assert(len <= 10);
        int best = 0;
        for (int mask = 0; mask < (1<<len); mask++) {
            int tot_w = 0, tot_v = 0;
            for (int i = 0; i < len; i++) {
                if ((mask >> i) & 1) {
                    tot_w += W[rest[i]];
                    tot_v += V[rest[i]];
                }
            }
            if (tot_w > l)
                continue;
            best = max(best, dp[v][l - tot_w] + tot_v);
        }
        cout << best << '\n';
    }

    return 0;
}