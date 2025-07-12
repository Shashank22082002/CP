/**
 * Minor Setbacks
 * Major Comebacks
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int MOD = 1E9 + 7;
const int N = 1E6 + 100;
const int MAX_DEPTH = 31;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // up pointers
    vector<vector<int>> up(n, vector<int>(MAX_DEPTH));

    for (int i = 0; i < n; i++) {
        up[i][0] = a[i] - 1;
    }

    for (int j = 1; j < MAX_DEPTH; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
            // cout << i << " " << j << " " << up[i][j] << endl;
        }
    }



    int x, k;
    
    auto findPar = [&] (int x, int k) {
        int par = x;
        int i = 0;
        while (k > 0) {
            if (k & 1ll) {
                par = up[par][i];
            }
            k >>= 1;
            ++i;
        }
        return par;
    };

    for (int _q = 0; _q < q; _q++) {
        cin >> x >> k;
        cout << findPar(x - 1, k) + 1 << "\n";
    }
}

int32_t main() {
    ios_base:: sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}