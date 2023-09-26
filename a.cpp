#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

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

const int N = 2E5 + 69;
const int INF = 1E18;
const int MOD = 1E9 + 7;

void solve() {
    string s;
    cin >> s;
    if (s == "abc") {
        cout << "YES\n";
        return;
    }
    string t1 = s, t2 = s, t3 = s;
    swap(t1[0], t1[1]);
    swap(t2[1], t2[2]);
    swap(t3[0], t3[2]);
    if (t1 == "abc" || t2 == "abc" || t3 == "abc") {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        solve();
    }
}