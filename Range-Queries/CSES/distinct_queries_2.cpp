// Logic : If all numbers from l..r are distinct, then minimum value of next index of all elements in (l, r) >= r

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"


const int MOD = 1E9 + 7;
const int N = 1E6 + 100;
const int B = 500;

template <typename T>
class segTreeMin {
public:
    vector <T> st;
    int _n;
    segTreeMin(int n) {
    	_n = n;
        st.resize(4 * n, 0);
    }
    /**  
     * Change this function as requirement
     */
    T func(T a, T b) {
        return min(a, b);
    }
 
    void build(int node, int start, int end, vector<T> &arr) {
        if (start == end) {
            st[node] = arr[start];
        } else {
            int mid = (start + end)/2;
            build(2*node + 1, start, mid, arr);
            build(2*node + 2, mid+1, end, arr);
            st[node] = func(st[2*node + 1], st[2*node + 2]);
        }
    }
    
    /**
     * Point update in O(logn)
     */
 
    void update(int node, int start, int end, int pos, T val) {
        if(start == end) {
            st[node] = val;
        } else {
            int mid = (start + end)/2;
            if(pos <= mid) {
                update(2*node + 1, start, mid, pos, val);
            } else {
                update(2*node + 2, mid + 1, end, pos, val);
            }
            st[node] = func(st[2*node + 1], st[2*node + 2]);
        }
    }
    
    /**
     * Range query -- O(logn) per query
     * Function value from [l .. r] (closed)
     */
 
    T query(int node, int start, int end, int l, int r) {
        if(l > r) {
            return _n;
        }
        if(l == start && r == end) {
            return st[node];
        }
        int mid = (start + end)/2;
        int left = query(2*node + 1, start, mid, l, min(mid, r));
        int right = query(2*node + 2, mid + 1, end, max(l, mid + 1), r);
        return func(left, right);
    }
};


void solve() {
    int n, q, t, l, r, k, u;
    cin >> n >> q;
    vector<int> v(n), next_idx(n, n + 1), prev_idx(n, -1);
    map<int, int> mp;
    map<int, set<int>> idxs;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (mp.find(v[i]) == mp.end()) {
            mp[v[i]] = i;
        } else {
            prev_idx[i] = mp[v[i]];
            next_idx[mp[v[i]]] = i;
            mp[v[i]] = i;
        }
        idxs[v[i]].insert(i);
    }

    segTreeMin<int> tree(n);
    tree.build(0, 0, n - 1, next_idx);

    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> k >> u;
            --k;
            int prev = prev_idx[k];
            int next = next_idx[k];
            if (next != n + 1) {
                prev_idx[next] = prev;
            }
            if (prev != -1) {
                next_idx[prev] = next;
                tree.update(0, 0, n - 1, prev, next);
            }
            idxs[v[k]].erase(idxs[v[k]].find(k));
            v[k] = u;
            auto &idx = idxs[u];
            if (idx.size() == 0) {
                tree.update(0, 0, n - 1, k, n + 1);
                next_idx[k] = n + 1;
                prev_idx[k] = -1;
                idx.insert(k);
                continue;
            }
            auto next_itr = idx.lower_bound(k);
            if (next_itr == idx.begin()) {
                next = *next_itr;
                next_idx[k] = next;
                tree.update(0, 0, n - 1, k, next);
                prev_idx[next] = k;
                idx.insert(k);
            } else if (next_itr == idx.end()) {
                prev = *(--next_itr);
                next_idx[prev] = k;
                prev_idx[k] = prev;
                tree.update(0, 0, n - 1, prev, k);
                idx.insert(k);
            } else {
                next = *next_itr;
                prev = *(--next_itr);
                next_idx[k] = next;
                next_idx[prev] = k;
                prev_idx[next] = k;
                prev_idx[k] = prev;
                tree.update(0, 0, n - 1, k, next);
                tree.update(0, 0, n - 1, prev, k);
                idx.insert(k);
            }
        } else {
            cin >> l >> r;
            --l, --r;
            int min_idx = tree.query(0, 0, n - 1, l, r);
            if (min_idx > r) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
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