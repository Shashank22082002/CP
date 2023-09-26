// nice problem -- optimisations on dp


#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;
const int maxn = 3001;
const int MOD = 1E9 + 7;
int pre[2][maxn];

void solve() {
    cin >> n;
    cin >> s;
    s = '<' + s;
    pre[n & 1][0] = 1;
    for (int i = 0; i <= n; i++) {
        pre[n & 1][i + 1] = pre[n & 1][i] + (i == 0);
    }
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int l = 0; l <= n; l++) {
            int sm = n - l - i;
            int val = 0;
            if (s[i] == '<') {
                val = (pre[(i + 1) & 1][l] - pre[(i + 1) & 1][0] + MOD) % MOD;
            } else {
                if(sm > 0)
                    val = (pre[(i + 1) & 1][l + sm] - pre[(i + 1) & 1][l] + MOD) % MOD;
            }
            ans = val;
            pre[i & 1][l + 1] = (pre[i & 1][l] + ans) % MOD;
        }
    }
    cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	solve();
}