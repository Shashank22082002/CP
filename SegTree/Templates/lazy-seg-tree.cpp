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
