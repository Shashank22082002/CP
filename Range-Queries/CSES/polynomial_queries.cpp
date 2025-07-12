/**
 * Minor Setbacks
 * Major Comebacks
 * 
 */

// Third application of powerful template
// https://cses.fi/problemset/task/1736/


#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"


const int MOD = 1E9 + 7;
const int N = 1E6 + 100;
const int B = 500;

template<typename T, typename U>
class LazySegTree {
private:
    int n;
    vector<T> st;
    vector<U> lazy;
    T SID; // Segment identity (e.g., 0 for sum, INF for min)
    U LID; // Lazy identity (e.g., 0 for add, -1 for no-op)

    function<T(T, T)> combine;                       // Combine two segments
    function<void(T&, U, int, int)> apply_update;    // Apply lazy update to segment
    function<U(U, U)> merge_lazy;                    // Merge two lazy values
    function<U(U, T)> shift_lazy;

    void build(int node, int l, int r, const vector<T>& a) {
        if (l == r) {
            st[node] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * node + 1, l, m, a);
            build(2 * node + 2, m + 1, r, a);
            pull(node);
        }
    }

    void push(int node, int l, int r) {
        if (lazy[node] != LID) {
            apply_update(st[node], lazy[node], l, r);
            if (l != r) {
                lazy[2 * node + 1] = merge_lazy(lazy[2 * node + 1], lazy[node]);
                int m = (l + r) / 2;
                int lenLeft = m - l + 1;
                lazy[2 * node + 2] = merge_lazy(lazy[2 * node + 2], shift_lazy(lazy[node], lenLeft));
            }
            lazy[node] = LID;
        }
    }

    void pull(int node) {
        st[node] = combine(st[2 * node + 1], st[2 * node + 2]);
    }

    void update(int node, int l, int r, int ql, int qr, U val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] = merge_lazy(lazy[node], val);
            push(node, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(2 * node + 1, l, m, ql, qr, val);
        update(2 * node + 2, m + 1, r, ql, qr, val);
        pull(node);
    }

    T query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return SID;
        if (ql <= l && r <= qr) return st[node];
        int m = (l + r) / 2;
        return combine(
            query(2 * node + 1, l, m, ql, qr),
            query(2 * node + 2, m + 1, r, ql, qr)
        );
    }

public:
    LazySegTree(T _SID, U _LID,
            function<T(T, T)> _combine,
            function<void(T&, U, int, int)> _apply_update,
            function<U(U, U)> _merge_lazy,
            function<U(U, int)> _shift_lazy)
    : SID(_SID), LID(_LID),
      combine(_combine), apply_update(_apply_update), merge_lazy(_merge_lazy), shift_lazy(_shift_lazy) {}

    void build(const vector<T>& a) {
        n = a.size();
        st.assign(4 * n, SID);
        lazy.assign(4 * n, LID);
        build(0, 0, n - 1, a);
    }

    void update(int l, int r, U val) {
        update(0, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};


void solve() {
    int n, q, t, a, b;
    cin >> n >> q;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    auto combine = [&](int a, int b) {
        return a + b;
    };

    auto apply_update = [&](int &st, pair<int, int> up, int l, int r) {
        int ct = r - l + 1;
        // up.first is start val
        // up.second is skip val
        // up.first + up.first + up.second + up.first + 2 * up.second ... up.first + (ct - 1).up.second
        st += up.first * ct + up.second * ((ct * (ct - 1)) / 2);
    };

    auto merge_lazy = [&](pair<int, int> up1, pair<int, int> up2) {
        return make_pair(up1.first + up2.first, up1.second + up2.second);
    };

    auto shift_lazy = [&](pair<int, int> lazy_val, int shift_by) {
    // shift start value ahead in AP
        return make_pair(lazy_val.first + lazy_val.second * shift_by, lazy_val.second);
    };

    int SID = 0;
    pair<int, int> LID = {0, 0};

    LazySegTree<int, pair<int, int>> st(SID, LID, combine, apply_update, merge_lazy, shift_lazy);
    st.build(v);

    for (int i = 0; i < q; i++) {
        cin >> t >> a >> b;
        --a, --b;
        if (t == 1) {
            st.update(a, b, {1ll, 1ll});
        } else {
            cout << st.query(a, b) << "\n";
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