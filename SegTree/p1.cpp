// https://codeforces.com/problemset/problem/1847/D

#include <bits/stdc++.h>
using namespace std;

const int N = 2E5 + 7;
vector<int> st(4 * N);
vector<int> v;
void build(int node, int l, int r) {
    if (l == r) {
        st[node] = v[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node + 1, l, mid);
    build(2 * node + 2, mid + 1, r);
    st[node] = st[2 * node + 1] + st[2 * node + 2];
}

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        st[node] = val;
    } else {
        int mid = (l + r) / 2;
        if (idx > mid) {
            update(2 * node + 2, mid + 1, r, idx, val);
        } else {
            update(2 * node + 1, l, mid, idx, val);
        }
        st[node] = st[2 * node + 1] + st[2 * node + 2];
    }
}

int query(int node, int l, int r, int p, int q) {
    if (p == l && q == r) {
        return st[node];
    }
    int mid = (l + r) / 2;
    if (p > mid) {
        return query(2*node + 2, mid + 1, r, p, q);
    }
    if (q <= mid) {
        return query(2*node + 1, l, mid, p, q);
    }
    int x1 = query(2*node + 1, l, mid, p, mid);
    int x2 = query(2*node + 2, mid + 1, r, mid + 1, q);
    return x1 + x2;
}

int main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    int n, m, q, l, r, x;
    cin >> n >> m >> q;
    string s;
    cin >> s;
    int ct = count(s.begin(), s.end(), '1');
    set<int> sx;
    vector<int> idx;
    for (int i = 0; i < n; i++) {
        sx.insert(i);
    }
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        --l, --r;
        while (true) {
            auto it = sx.lower_bound(l);
            if (it == sx.end() || *it > r) break;
            idx.push_back(*it);
            sx.erase(it);
        }
    }
    assert(idx.size() <= n);
    vector<int> index(n, -1);
    int sz = idx.size();
    for (int i = 0; i < sz; i++) {
        v.push_back(s[idx[i]] - '0');
        index[idx[i]] = i;
    }
    build(0, 0, sz - 1);
    for (int i = 0; i < q; i++) {
        cin >> x;
        --x;
        if (s[x] == '0') {
            s[x] = '1';
            ct++;
        } else {
            s[x] = '0';
            ct--;
        }
        int id = index[x];
        if (id != -1) {
            update(0, 0, sz - 1, id, v[id] ^ 1);
            v[id] ^= 1;
        }
        if (ct == 0) {
            cout << 0 << "\n";
            continue;
        }
        int mx = min(sz - 1, ct - 1);
        cout << mx + 1 - query(0, 0, sz - 1, 0, mx) << "\n";
    }
    return 0;
}