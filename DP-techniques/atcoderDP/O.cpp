// Matching problem
// important optimisations : 
// 1. Need not have i = No of Mens, as a state : it should be same as pop count of the mask
// 2. Space optimisation newly learned trick

#include <bits/stdc++.h>
using namespace std;
#define intt int32_t
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
typedef long long ll;
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}
 
 
#define showVVI(arr)           \
{                              \
    for (auto &vvv : arr)      \
    {                          \
        for (auto &xxxx : vvv) \
            csp(xxxx);         \
        cout << endl;          \
    }                          \
}
 
const int INF = 2e9 + 7;
const int MOD = 1E9 + 7;

int dp[1<<21];

void add_self(int& a, int& b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> v(n + 1, vector<int> (n + 1));
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> v[i][j];
        }
    }
    for(int mask = 0; mask < (1 << n); mask++) {
        int i = __builtin_popcount(mask);
        for(int j = 1; j <= n; j++) {
            if(v[i][j] && ((mask >> (j - 1)) & 1))
                add_self(dp[mask], dp[mask - (1 << (j - 1))]);
        }
    }
    cout << dp[(1 << n) - 1] << endl;
}
 
intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    for(int _t = 0; _t < t; _t++)
        solve();
    return 0;
}