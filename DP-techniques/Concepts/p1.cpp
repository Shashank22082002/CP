#include <bits/stdc++.h>
using namespace std;

#define int long
const int INF = 1E9;
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
void amax(int &a, int b) {
    a = max(a, b);
}

int dp[3001][3001][5], diagMax[3002][3002][5];

void solve() {
    int n, L;
    cin >> n >> L;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {
            for (int k = 0; k < 5; k++)
                dp[i][j][k] = diagMax[i][j][k] = -INF;
        }
    }
    // vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (L + 1, vector<int> (5, -INF)));
    // vector<vector<vector<int>>> diagMax(n + 2, vector<vector<int>> (L + 2, vector<int> (5, -INF)));
    // for (int l = 0; l <= L; l++) {
    //     amax(diagMax[l][l][1])
    // }
    // for (int i = 0; i <= n; i++) {
    //     for (int k = 0; k < 5; k++) {
    //         dp[i][0][k] = 0;
    //     }
    //     diagMax[i + 1][1][1] = b[i] - a[i];
    //     diagMax[i + 1][1][2] = - b[i] - a[i];
    //     diagMax[i + 1][1][3] = b[i] + a[i];
    //     diagMax[i + 1][1][4] = - b[i] + a[i];
    // }
    for (int k = 0; k < 5; k++)
    dp[0][0][k] = 0;
    // diagMax[1][1][1] = b[1] - a[1];
    // diagMax[1][1][2] = - b[1] - a[0];
    // diagMax[1][1][3] = b[1] + a[1];
    // diagMax[1][1][4] = - b[1] - a[1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= L; j++) {
            if (i > 0 && j > 0)
            for (int k = 0; k < 5; k++) {
                amax(diagMax[i][j][k], diagMax[i - 1][j - 1][k]);
            }

            // take no segment
            if (i > 0) {
                for (int k = 0; k < 5; k++) {
                    amax(dp[i][j][0], dp[i - 1][j][k]);
                }
                // case 1 : br - ar + bl - al
                dp[i][j][1] = diagMax[i][j][1] + b[i] - a[i];

                // case 2: br + ar - al - bl
                dp[i][j][2] = diagMax[i][j][2] + a[i] + b[i];

                // case 3: bl + al - br - ar
                // if(i == 2 && j == 2) {
                //     cout << "here " << diagMax[i][j][3] << endl;
                // }
                dp[i][j][3] = diagMax[i][j][3] - a[i] - b[i];

                // case 4: ar - br + al - bl
                dp[i][j][4] = diagMax[i][j][4] + a[i] - b[i];
            }
            
            if (i < n)
            {
                for (int k = 0; k < 5; k++) {
                    amax(diagMax[i + 1][j + 1][1], dp[i][j][k] + b[i + 1] - a[i + 1]);
                    amax(diagMax[i + 1][j + 1][2], dp[i][j][k] - b[i + 1] - a[i + 1]);
                    // if(i == 0 && j == 0) {
                    //     cout << "here " << dp[i][j][3] + b[i + 1] + a[i + 1] << endl;
                    // }
                    amax(diagMax[i + 1][j + 1][3], dp[i][j][k] + b[i + 1] + a[i + 1]);
                    amax(diagMax[i + 1][j + 1][4], dp[i][j][k] - b[i + 1] + a[i + 1]);
                }
            }
        }
    }
    // showVVI(dp[4]);
    int ans = 0;
    for (int k = 0; k < 5; k++) {
        amax(ans, dp[n][L][k]);
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int _t = 0; _t < t; _t++) {
        solve();
    }
    return 0;
}