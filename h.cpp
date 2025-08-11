#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

int MAXT = 1E6 + 1;

void solve() {
    int n, k, q, id, ts;
    cin >> n >> k >> q;
    vector<vector<int>> ping_logs;
    vector<pair<int, int>> queries;
    
    for (int i = 0; i < n; i++) {
        cin >> id >> ts;
        ping_logs.push_back({id, ts});
    }

    for (int i = 0; i < q; i++) {
        cin >> ts;
        queries.push_back({ts, i});
    }

    // sort on timestamp
    sort(ping_logs.begin(), ping_logs.end(), [](const vector<int> &A, const vector<int> &B){
        return A[1] < B[1];
    });

    sort(queries.begin(), queries.end());
    map<int, int> window;

    int left = 0, right = 0;
    vector<int> ans(q);

    for (auto &q : queries) {
        int st = q.first - k, en = q.first, idx = q.second;
        
        while (right < n && ping_logs[right][1] <= en) {
            window[ping_logs[right][0]]++;
            right++;
        }

        while (left < n && ping_logs[left][1] < st) {
            int id = ping_logs[left][0];
            window[id]--;
            if (window[id] == 0) {
                window.erase(window.find(id));
            }
            left++;
        }

        ans[idx] = n - window.size();

    }
    
    for (auto val : ans) cout << val << " ";
    cout << "\n";

}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}