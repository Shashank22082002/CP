#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1E9 + 7;
const int N = 1E5 + 69;

void add_self(int &a, int b) {
	a += b;
	if (a > MOD)
		a -= MOD;
}
const int maxn = 10123;
const int maxd = 100;
int dp[2][maxd][maxn];
int f(int i, int val, int d, bool tight, string &num) {
    if (dp[tight][val][i] != -1)
        return dp[tight][val][i];
    if (i == num.size()) {
        return val == 0;
    }
    int lb = 0, ub = tight ? (num[i] - '0') : 9;
    int sum = 0;
    for (int v = lb; v <= ub; v++) {
        add_self(sum, f(i + 1, (val + v) % d, d, tight && (v == ub), num));
    }
    return dp[tight][val][i] = sum;
}


void solve() {
	string k;
    int d;
    cin >> k >> d;
    memset (dp, -1, sizeof dp);
    cout << (f(0, 0, d, 1, k) - 1 + MOD) % MOD << endl;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	solve();
}