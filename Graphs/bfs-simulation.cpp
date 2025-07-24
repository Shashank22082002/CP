// https://cses.fi/problemset/task/1194/
// Very nice problem on BFS simulation

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1E9;
const vector<tuple<int, int, char>> DIRS = {{-1, 0, 'U'}, {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}};

void solve() {
    int n, m;
    string s;
    cin >> n >> m;
    vector<string> v(n);
    vector<vector<int>> dis(n, vector<int> (m, INF));
    queue<pair<int, int>> q;
    pair<int, int> A;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        for (int j = 0; j < m; j++) {
            if (v[i][j] == 'M') {
                dis[i][j] = 0;
                q.emplace(i, j);
            }
            if (v[i][j] == 'A') {
                A.first = i, A.second = j;
            }
        }
    }
    while (!q.empty()) {
        auto &[x, y] = q.front(); q.pop();
        for (auto &[dx, dy, d] : DIRS) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || v[nx][ny] == '#' || dis[nx][ny] <= 1 + dis[x][y])
                continue;
            dis[nx][ny] = 1 + dis[x][y];
            q.emplace(nx, ny);
        }
    }

    q.emplace(A.first, A.second);
    vector<vector<int>> pdis(n, vector<int> (m, INF));
    pdis[A.first][A.second] = 0;
    unordered_map<int, pair<int, char>> par;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto &[dx, dy, d] : DIRS) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
                cout << "YES\n";
                string path = "";
                int cx = x, cy = y;
                while (true) {
                    if ((cx == A.first) && (cy == A.second))
                        break;
                    int idx = cx * m + cy;
                    assert(par.find(idx) != par.end());
                    auto &[pdx, dir] = par[idx];
                    path += dir;
                    cx = pdx / m, cy = pdx % m;
                }
                cout << path.size() << "\n";
                reverse(path.begin(), path.end());
                cout << path;
                return;
            }
            if (v[nx][ny] == '#' || (pdis[x][y] + 1) >= dis[nx][ny] || pdis[x][y] + 1 >= pdis[nx][ny])
                continue;
            pdis[nx][ny] = 1 + pdis[x][y];
            par[nx * m + ny] = {x * m + y, d};
            q.emplace(nx, ny);
        }
    }
    cout << "NO\n";
    
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}