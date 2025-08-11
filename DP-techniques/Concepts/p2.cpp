/**
Great optimisation problem
from O(n * k) Time and O(n) space to
O(n) time and O(k) space


Problem : 
The generator has to generate a total of n files, with k different file types under the following conditions:
• The files are always ordered in the order of generation
• There can be at most (k-1) consecutive files with the same type


DP Technique -- deque optimisation

Cases
n = 3, k = 3
ans = 24

n = 10, k = 2
ans = 2

n = 10, k = 3
ans = 27408
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

int numOfWays(int n, int k) {
    vector<int> dp(n + 1);
    dp[1] = k;
    for (int i = 2; i <= n; i++) {
        int sum = 0;
        for (int j = i - 1; j >= max(1ll, i - k + 1); j--) {
            sum += dp[j] * (k - 1);
        }
        if (i - k + 2 <= 1) {
            sum += k;
        }
        dp[i] = sum;
    }
    return dp[n];
}

int numOfWaysOptimised(int n, int k) {
    // vector<int> dp(n + 1);
    // dp[1] = k;
    deque<int> dq;
    dq.push_back(k);
    int sum = k;
    int ans = k;

    // deque size is maximum k - 1
    // ways[i] = (ways[i - 1] + ways[i - 2] + .. ways[i - (k - 1)]) * (k - 1)
    
    for (int i = 2; i <= n; i++) {
        if (dq.size() >= k - 1) {
            ans = sum * (k - 1);
            dq.push_back(ans);
            sum += ans;
            sum -= dq.front();
            dq.pop_front();
        } else {
            ans = k + sum * (k - 1);
            dq.push_back(ans);
            sum += ans;
        }
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    cout << numOfWaysOptimised(n, k) << endl;
    cout << numOfWays(n, k) << endl;
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}