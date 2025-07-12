#include <bits/stdc++.h>
using namespace std;
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long

void solve() {
    int n, q, l, r;
    cin >> n >> q;
    vector<int> v(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 2; i <= n; i++) c[i] = c[i - 1] + (v[i] < v[i - 1] ? v[i - 1] - v[i] : 0);
    for (int i = 0; i <= n; i++) cout << c[i] << " ";
    cout << "\n";
    while (q--) {
        cin >> l >> r;
        cout << c[r - 1] - c[l - 1] << "\n";
    }
}

int32_t main () {
    FIO;
    solve();
}