// problem lucky queries https://codeforces.com/contest/145/problem/E


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

const int mod = (int)1e9+7;


template <typename T, typename U>
class lazySegTree {
public:
    int n;
    
    // stores the count 7's in the range
    vector<T> st;
    
    // stores the maximum subsequence length in the range
    vector<T> slen;
    // stores reverse maximum
    vector<T> tlen;
    
    
    vector<U> lazy;
    
    // Identity element for segment tree data
    T SID = INT_MAX;
    
    // Identity element for lazy update
    U LID = 0;
    
    T comb(T a, T b) {
        return a + b;
    }
    
    lazySegTree(int _n) : n(_n) {
        st.resize(4 * n, 0);
        slen.resize(4 * n, 0);
        tlen.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    
    void build(int node, int l, int r, vector<T> &v) {
        if(l == r) {
            st[node] = v[l];
            slen[node] = 1;
            tlen[node] = 1;
        } else {
            int m = (l + r)/2;
            build(2*node + 1, l, m, v);
            build(2*node + 2, m+1, r, v);
            pull(node, l, r);
        }
    }
    
    void pull(int node) {
        st[node] = comb(st[2*node + 1], st[2*node + 2]);
    }
    
    void pull(int node, int l, int r) {
        st[node] = comb(st[2*node + 1], st[2*node + 2]);
        // take 4's from left and slen from right
        // take slen from left and 7's from right
        int m = (l + r)/2;
        int ct0 = (m-l+1) - st[2*node + 1];
        int ct1 = (r - m) - st[2*node + 2];
        slen[node] = max(ct0 + slen[2*node + 2], slen[2*node + 1] + st[2*node + 2]);
        tlen[node] = max(tlen[2*node + 1] + ct1, st[2*node + 1] + tlen[2*node + 2]);
        // cout << slen[node] << " " <<  l << " " << r << endl;
    }
    
    void push(int node, int l, int r) {
        if(lazy[node]) {
            st[node] = (r-l+1)-st[node];
            int temp = slen[node];
            slen[node] = tlen[node];
            tlen[node] = temp;
        }
        if(l != r) {
            lazy[2*node + 1] = lazy[2*node + 1] ^ lazy[node];
            lazy[2*node + 2] = lazy[2*node + 2] ^ lazy[node];
        }
        lazy[node] = LID;
    }
    
    void apply(int l, int r) {
        return apply(0, 0, n-1, l, r);
    }
    
    
    void apply(int node, int tl, int tr, int l, int r) {
        // tl and tr are tree left and right
        // apply val on range [l .. r] => increases value by val
        // cout << tl << " " << tr << " " << l << " " << r <<  endl;
        push(node, tl, tr);
        
        // do not intersect
        if (r < tl || tr < l) return;
        
        // completely overlaps(lies inside) with [l..r]
        if (l <= tl && tr <= r) {
            lazy[node] = (lazy[node] ^ 1);
            push(node, tl, tr);
            return;
        }
        
        // intersects
        int tm = (tl + tr)/2;
        apply(2*node + 1, tl, tm, l, r);
        apply(2*node + 2, tm+1, tr, l, r);
        pull(node, tl, tr);
    }
    
    T query(int l, int r) {
        return query(0, 0, n-1, l, r);
    }
    
    T query(int node, int tl, int tr, int l, int r) {
        push(node, tl, tr);
        
        // lies outside
        if(r < tl || tr < l) return SID;
        
        // lies inside
        if(l <= tl && tr <= r) return st[node];
        
        int tm = (tl + tr)/2;
        return comb(query(2*node+1, tl, tm, l, r), query(2*node + 2, tm + 1, tr, l, r));
    }
    
    T querySubseq(int node, int tl, int tr, int l, int r) {
        push(node, tl, tr);
        
        // lies outside
        if(r < tl || tr < l) return SID;
        
        // lies inside
        if(l <= tl && tr <= r) return slen[node];
        
        int tm = (tl + tr)/2;
        int op1 = querySubseq(2*node+1, tl, tm, l, r) + query(2*node+2, tm+1, tr, l, r);
        int op2 = (max(l, tl) - min(r, tm) + 1) - query(2*node+1, tl, tm, l, r) + querySubseq(2*node+2, tm+1, tr, l, r);
        return max(op1, op2);
    }
    
    T querySubseq(int l, int r) {
        return querySubseq(0, 0, n-1, l, r);
    }
};


void solve() {
    int n, m, l, r;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        if(s[i] == '7')
            v[i]++;
    }
    
    lazySegTree<int, int> st(n);
    st.build(0, 0, n-1, v);
    
    for(int i = 0; i < m; i++) {
        cin >> s;
        if(s == "count") {
            cout << st.querySubseq(0, n-1) << endl;
        }
        else {
            cin >> l >> r;
            --l, --r;
            st.apply(l, r);
        }
    }
}


intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t = 1;
    // cin >> t;
    for(int i = 0; i < t; i++) solve();
    return 0;
}
