// https://codedrills.io/contests/icpc-algoqueen-2023-prelims/problems/query-and-xor

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base:: sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    int n, q, l, r, x, xv = 0;
    cin >> n;
    int v[n];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        xv ^= v[i];
    }
    int m[n][20]; // m[i][j] denotes next occurance of jth bit after i
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 20; j++)
        m[i][j] = i + 1;
    }
    cin >> q;
    while (q--) {
        cin >> l >> r >> x;
        --l, --r;
        for (int b = 0; b < 20; b++) {
            if (!((1 << b) & x)) {
                // b bit has to be unset from l .. r
                for (int i = l; i <= r; i++) {
                    if ((1 << b) & v[i]) {
                        v[i] ^= (1 << b);
                        xv ^= (1 << b);
                    }
                    int f = m[i][b] - 1;
                    m[i][b] = max(m[i][b], r + 1);
                    i = f;
                }
            }
        }
        cout << xv << "\n";
    }
    return 0;
}