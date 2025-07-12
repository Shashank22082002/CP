// https://www.spoj.com/problems/SEGSQRSS/
// First application of powerful segtree template

/**
 * Minor Setbacks
 * Major Comebacks
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"


const int MOD = 1E9 + 7;
const int N = 1E6 + 100;

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
                lazy[2 * node + 2] = merge_lazy(lazy[2 * node + 2], lazy[node]);
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
    LazySegTree(int _n, T _SID, U _LID,
                function<T(T, T)> _combine,
                function<void(T&, U, int, int)> _apply_update,
                function<U(U, U)> _merge_lazy)
        : n(_n), SID(_SID), LID(_LID),
          combine(_combine), apply_update(_apply_update), merge_lazy(_merge_lazy)
    {
        st.assign(4 * n, SID);
        lazy.assign(4 * n, LID);
    }

    void build(const vector<T>& a) {
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
    int n, q, t, l, r, x;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = v[i].first * v[i].first;
    }

    auto SID = pair<int, int> (0, 0);
    auto TID = pair<int, bool> (0, false);
    auto combine = [](pair<int, int> n1, pair<int, int> n2) {
        return pair<int, int> (
            n1.first + n2.first,
            n1.second + n2.second
        );
    };

    auto apply_lazy = [](pair<int, int> &node, pair<int, bool> update, int l, int r) {
        int val = update.first;
        int len = r - l + 1;
        if (update.second) {
            // set update
            node.first = val * len;
            node.second = val * val * len;
        } else {
            // add update
            int original_sum = node.first;
            node.first += val * len;
            node.second += 2 * val * original_sum + val * val * len;
        }
    };

    auto merge_lazy = [](pair<int, bool> up1, pair<int, bool> up2) {
        if (up2.second) return up2;
        if (up1.second) return pair<int, bool> (up1.first + up2.first, true);
        return pair<int, bool> (up1.first + up2.first, false);
    };

    auto tree = LazySegTree<pair<int, int>, pair<int, bool>>(
        n,
        SID,
        TID,
        combine,
        apply_lazy,
        merge_lazy
    );
    
    tree.build(v);

    for (int i = 0; i < q; i++) {
        cin >> t >> l >> r;
        --l, --r;
        if (t == 2) {
            cout << tree.query(l, r).second << "\n";
        } else if (t == 1) {
            cin >> x; 
            // add x in range l, r
            tree.update(l, r, pair<int, bool>(x, false));
        } else {
            cin >> x;
            // set
            tree.update(l, r, pair<int, bool> (x, true));
        }
    }
    
}

int32_t main() {
    int t = 1;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case " << i + 1 << ":\n";
        solve();
    }
    return 0;
}