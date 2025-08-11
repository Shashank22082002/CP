#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

int countLatticePoints(vector<vector<int>>& circles) {
    int n = circles.size();
    int points = 0;
    for (int x = 0; x <= 600000; x++) {
        vector<pair<int, int>> intervals;
        for (auto circle : circles) {
            int a = circle[0], b = circle[1], r = circle[2];
            // (y - b)^2 = r ^ - (x1 - a)^2 .. find integer y's
            int rhs = r * r - (x - a) * (x - a);
            if (rhs < 0)
                continue;

            // need to test / handle perfect square case
            double root = sqrt(rhs);
            double L = b - root; // integer greater than this
            double R = b + root; // integer smaller than this
            if (ceil(L) <= floor(R))
                intervals.push_back({ceil(L), floor(R)});
        }

        if (intervals.empty())
            continue;

        // now I have some intervals.. need to find the pts covered
        // sort on start and maintain start and end
        sort(intervals.begin(), intervals.end());
        int line = -1, ans = 0;
        // cout << "X = " << x << endl;
        for (auto &interval : intervals) {
            if (line >= interval.second)
                continue;
            // cout << interval.first << " " << interval.second;
            if (line < interval.first) {
                ans += interval.second - interval.first + 1;
                line = interval.second;
            } else {
                ans += interval.second - line;
                line = interval.second;
            }
            // cout << " ans " << ans << "\n";
        }
        points += ans;
    }
    return points;
}

void solve() {
    int n, a, b, r;
    cin >> n;
    vector<vector<int>> circles;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> r;
        circles.push_back({a, b, r});
    }
    cout << countLatticePoints(circles) << "\n";
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