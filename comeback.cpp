#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

void solve() {
    auto findVars = [&](string str) {
        int n = str.size();
        vector<string> vars;
        for (int i = 0; i < n; i++) {
            if (str[i] == '$') {
                // start of a variable
                string var = "";
                for (int j = i + 1; j < n; j++) {
                    if (str[j] == '$') {
                        // end of variable
                        i = j;
                        break;
                    }
                    var += str[j];
                }
                vars.push_back(var);
            }
        }
        return vars;
    };
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s;
        vector<int> vars = g
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}