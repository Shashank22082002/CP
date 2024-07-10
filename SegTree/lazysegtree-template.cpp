#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 1e9+7;

template <typename T, typename U>
class lazySegTree {
public:
	int n;
	vector<T> st;
	vector<U> lazy;
	
	// Identity element for segment tree data
	T SID = INT_MAX;
	
	// Identity element for lazy update
	U LID = 0;
	
	T comb(T a, T b) {
		return min(a, b);
	}
	
	lazySegTree(int _n) : n(_n) {
		st.resize(4 * n, SID);
		lazy.resize(4 * n, LID);
	}
	
	void build(int node, int l, int r, vector<T> &v) {
		if(l == r) {
			st[node] = v[l];
		} else {
			int m = (l + r)/2;
			build(2*node + 1, l, m, v);
			build(2*node + 2, m+1, r, v);
			pull(node);
		}
	}
	
	void pull(int node) {
		st[node] = comb(st[2*node + 1], st[2*node + 2]);
	}
	
	void push(int node, int l, int r) {
		st[node] += lazy[node]; // for sum multiply by (r - l + 1)
		
		if(l != r) {
			lazy[2*node + 1] += lazy[node];
			lazy[2*node + 2] += lazy[node];
		}
		lazy[node] = LID;
	}
	
	void apply(int l, int r, int val) {
		return apply(0, 0, n-1, val, l, r);
	}
	
	void apply(int node, int tl, int tr, T val, int l, int r) {
		// tl and tr are tree left and right
		// apply val on range [l .. r] => increases value by val
		push(node, tl, tr);
		
		// do not intersect
		if (r < tl || tr < l) return;
		
		// completely overlaps(lies inside) with [l..r]
		if (l <= tl && tr <= r) {
			lazy[node] += val;
			push(node, tl, tr);
			return;
		}
		
		// intersects
		int tm = (tl + tr)/2;
		apply(2*node + 1, tl, tm, val, l, r);
		apply(2*node + 2, tm+1, tr, val, l, r);
		pull(node);
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
};


void solve()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
    	cin >> v[i];
    int q;
    cin >> q;
    // int t, l, r, w;
    lazySegTree<int, int> st(n);
    st.build(0, 0, n-1, v);
    string s; 
    getline(cin, s);
   
    for(int i = 0; i < q; i++) {
    	getline(cin, s);
		stringstream iss(s);
		int l, r, v; 
		iss >> l >> r;
		if (iss >> v) {
			if(r < l) {
				st.apply(l, n-1, v);
				st.apply(0, r, v);
			} else {
				st.apply(l, r, v);
			}
		} else {
			if(r < l) {
				cout << min(st.query(l, n-1), st.query(0, r)) << endl;
			} else {
				cout << st.query(l, r) << endl;
			}
		}
		
    }
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    
    solve();
}