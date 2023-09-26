#include <bits/stdc++.h>
using namespace std;

const int K = 1E5;
const int MOD = 1E9+7;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), prev(k+2, 1), curr(k+2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    prev[0] = 0;
    int var = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            int mx = max(0, j - a[i - 1]);
            var = (prev[j + 1] - prev[mx] + MOD) % MOD;
            curr[j+1] = (curr[j] + var) % MOD;
        }
        prev = curr;
    }

    cout << var << endl;
    return 0;
}