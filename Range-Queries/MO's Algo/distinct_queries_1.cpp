/**
 * Minor Setbacks
 * Major Comebacks
 * 
 * Distinct Queries 1 : Finding distinct elements in a range query
 * https://cses.fi/problemset/task/1734
 * 
 */



#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"


const int MOD = 1E9 + 7;
const int N = 1E6 + 100;
const int B = 500;

struct Query {
    int L, R, idx;
    bool operator<(const Query &other) const{
        if (L/B != other.L/B)
            return L/B < other.L/B;
        return R < other.R;
    }
};

void solve() {
    
    int n, q, l, r, idx = 0;
    cin >> n >> q;
    vector<int> a(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]] += 1;
    }

    // simple coordinate compression
    for (auto &it: mp) {
        it.second = ++idx;
    }

    for (int i = 0; i < n; i++) {
        a[i] = mp[a[i]];
    }

    vector<Query> qs;
    for (int i = 0; i < q; i++) {
        Query q;
        cin >> l >> r;
        q.L = --l;
        q.R = --r;
        q.idx = i;
        qs.push_back(q);
    }
    
    sort(qs.begin(), qs.end());

    int fre[N];
    int curr_ans = 0;

    auto add = [&](int idx) {
        fre[a[idx]] += 1;
        if (fre[a[idx]] == 1) {
            curr_ans += 1;
        }
    };

    auto remove = [&](int idx) {
        fre[a[idx]] -= 1;
        if (fre[a[idx]] == 0) {
            curr_ans -= 1;
        }
    };

    auto currAns = [&]() {
        return curr_ans;
    };

    vector<int> ans(q);

    int currL = 0, currR = -1;
    for (int i = 0; i < q; i++) {
        while (currR < qs[i].R) {
            currR++;
            add(currR);
        }

        while (currR > qs[i].R) {
            remove(currR);
            currR--;
        }

        while (currL < qs[i].L) {
            remove(currL);
            currL++;
        }

        while (currL > qs[i].L) {
            currL--;
            add(currL);
        }

        ans[qs[i].idx] = currAns(); 
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }

}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}