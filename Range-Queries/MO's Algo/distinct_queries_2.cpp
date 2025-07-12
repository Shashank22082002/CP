/**
 * Minor Setbacks
 * Major Comebacks
 * 
 * Distinct Queries 2 : Finding distinct elements in a range query with updates
 * https://cses.fi/problemset/task/3356
 * 
 */



#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"


const int MOD = 1E9 + 7;
const int N = 1E6 + 100;
const int B = 4000;

struct Update { 
    int idx, new_val, old_val;
};

struct Query {
    int L, R, T, idx;
    bool operator<(const Query &other) const{
        if (L/B != other.L/B)
            return L/B < other.L/B;
        if (R/B != other.R/B)
            return R/B < other.R/B;
        return T < other.T;
    }
};

void solve() {
    
    int n, q, l, r, t;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> vals;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals.push_back(a[i]);
    }

    vector<Query> qs;
    vector<Update> upds;
    for (int i = 0; i < q; i++) {
        cin >> t >> l >> r;
        if (t == 1) {
            Update u;
            u.idx = --l;
            u.old_val = a[l];
            u.new_val = r;
            upds.push_back(u);
            vals.push_back(r);
        } else {
            Query q;
            q.L = --l;
            q.R = --r;
            q.T = upds.size() - 1;
            q.idx = i - upds.size();
            qs.push_back(q);
        }
    }

    map<int, int> ranks;
    int rank = 0;
    for (auto &val: vals) {
        ranks[val]++;
    }

    for (auto &it: ranks) {
        it.second = ++rank;
    }

    for (int i = 0; i < n; i++) {
        a[i] = ranks[a[i]];
    }

    for (auto &up: upds) {
        up.old_val = ranks[up.old_val];
        up.new_val = ranks[up.new_val];
    }
    
    sort(qs.begin(), qs.end());

    int fre[N];
    int curr_ans = 0;
    int currL = 0, currR = -1, currT = -1;
    vector<int> ans(qs.size());

    auto add = [&](int idx) {
        fre[a[idx]]++;
        if (fre[a[idx]] == 1) {
            curr_ans++;
        }
    };

    auto remove = [&](int idx) {
        fre[a[idx]]--;
        if (fre[a[idx]] == 0) {
            curr_ans--;
        }
    };

    auto apply_update = [&](int idx) {
        int pos = upds[idx].idx;
        if (pos >= currL && pos <= currR) {
            remove(pos);
            a[pos] = upds[idx].new_val;
            add(pos);
        } else {
            a[pos] = upds[idx].new_val;
        }
    };

    auto revert_update = [&](int idx) {
        int pos = upds[idx].idx;
        if (pos >= currL && pos <= currR) {
            remove(pos);
            a[pos] = upds[idx].old_val;
            add(pos);
        } else {
            a[pos] = upds[idx].old_val;
        }
    };

    auto get_ans = [&]() {
        return curr_ans == (currR - currL + 1);
    };

    for (auto &qr: qs) {
        while (currT < qr.T) {
            currT++;
            apply_update(currT);
        }
        while (currT > qr.T) {
            revert_update(currT);
            currT--;
        }
        while (currR < qr.R) {
            currR++;
            add(currR);
        }
        while (currR > qr.R) {
            remove(currR);
            currR--;
        }
        while (currL < qr.L) {
            remove(currL);
            currL++;
        }
        while (currL > qr.L) {
            currL--;
            add(currL);
        }
        ans[qr.idx] = get_ans();
    }

    for (auto &it: ans) {
        if (it) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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