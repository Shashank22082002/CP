// Reaching end of matrix, with blockages
// Standard problem : https://atcoder.jp/contests/abc413/tasks/abc413_g

#include <bits/stdc++.h>
using namespace std;

#define int long long


const vector<pair<int, int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int H, W, K;
    cin >> H >> W >> K;
    vector<pair<int, int>> in(K + 1);
    set<pair<int, int>> blocks, vis;

    for (auto &[a, b] : in) {
        cin >> a >> b;
        blocks.insert({a, b});
    }

    queue<pair<int, int>> q;
    for (int i = 1; i <= H; i++) {
        if (blocks.find({i, 1ll}) != blocks.end())
            q.push({i, 1ll});
    }

    for (int i = 1; i <= W; i++) {
        if (blocks.find({H, i}) != blocks.end())
            q.push({H, i});
    }

    while (!q.empty()) {
        int a = q.front().first, b = q.front().second;
        q.pop();
        if (a == 1 || b == W) {
            cout << "No\n";
            return 0;
        }

        for (auto &[dx, dy]: dirs) {
            int na = a + dx, nb = b + dy;
            if (na <= 0 || nb <= 0 || na > H || nb > W || blocks.find({na, nb}) == blocks.end() || vis.find({na, nb}) != vis.end())
                continue;
            vis.insert({na, nb});
            q.push({na, nb});
        }
    }

    cout << "Yes\n";

    
    
    return 0;
}