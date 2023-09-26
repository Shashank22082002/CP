// DP with segtree --
// you need maximums of dp values for transistions -- and you cant just use prefix max's
// for prefix max's to be used the maximums should be updated consistently ...

#include <bits/stdc++.h>
using namespace std;
#define intt int32_t
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
typedef long long ll;
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}
 
 
#define showVVI(arr)           \
{                              \
    for (auto &vvv : arr)      \
    {                          \
        for (auto &xxxx : vvv) \
            csp(xxxx);         \
        cout << endl;          \
    }                          \
}
 
const int INF = 2e9 + 7;
const int MOD = 1E9 + 7;

/**
 * 0 based indexing !!
 * build(0, 0, n-1)...
 * tested on : https://codeforces.com/contest/1674/problem/F
 */
template <typename T>
class segTree {
public:
    vector <T> st;
    segTree(int n) {
        st.resize(4 * n, 0);
    }
    /**  
     * Change this function as requirement
     */
    T func(T a, T b) {
        return max(a, b);
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
            return 0;
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
    int n;
    cin >> n;
    vector<int> h(n), b(n), dp(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    segTree<int> st(n + 1);
    st.build(0, 0, n, dp);
    int ans = 0;
    for(int flower = 0; flower < n; flower++) {
        int maxi = st.query(0, 0, n, 0, h[flower] - 1) + b[flower];
        dp[h[flower]] = max(dp[h[flower]], maxi);
        st.update(0, 0, n, h[flower], dp[h[flower]]);
        ans = max(ans, dp[h[flower]]);
    }
    cout << ans << endl;
}
 
intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    for(int _t = 0; _t < t; _t++)
        solve();
    return 0;
}