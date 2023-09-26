// https://codeforces.com/contest/1641/problem/C
// Anonimity is important
// Long awaited to solve problem

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 1e9+7;
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}

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
	int n, q;
	cin >> n >> q;
	set<int> maybe;
	for (int i = 0; i < n; i++) {
		maybe.insert(i);
	}
	segTreeMin<int> stMin(n);
	vector<int> v(n, n);
	stMin.build(0, 0, n-1, v);
	int type, l, r, x;
	for (int i = 0; i < q; i++) {
		cin >> type;
		if (type == 0) {
			cin >> l >> r >> x;
			--l, --r;
			if (x == 0) {
				while (true) {
					auto it = maybe.lower_bound(l);
					if (it == maybe.end() || *it > r)
						break;
					maybe.erase(it);
				}
			} else {
				v[l] = min(v[l], r);
				stMin.update(0, 0, n-1, l, v[l]);
			}
		} else {
			cin >> x;
			--x;
			if (maybe.find(x) == maybe.end()) {
				cout << "NO\n";
				continue;
			}
			auto it = maybe.find(x);
			int l = 0, r = n;
			if (it != maybe.begin())
				l = *prev(it) + 1;
			it++;
			if (it != maybe.end())
				r = *it;
			int mini = stMin.query(0, 0, n-1, l, x);
			if (mini < r) {
				cout << "YES\n";
			} else {
				cout << "N/A\n";
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