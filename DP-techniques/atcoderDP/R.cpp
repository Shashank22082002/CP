// concept related to adjacency lists
// v[i][j] denotes number of paths of length 1 from (i, j)
// v^k denotes number of paths of length k

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1E9 + 7;
const int N = 1E5 + 69;

void add_self(int &a, int b) {
	a += b;
	if (a > MOD)
		a -= MOD;
}


void solve() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> v(n, vector<int> (n));
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			cin >> v[i][j];
	
	auto multiply = [&](vector<vector<int>> &a, vector<vector<int>> &b) -> vector<vector<int>> {
		vector<vector<int>> res(n, vector<int> (n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					add_self(res[i][j], a[i][k] * b[k][j] % MOD);
				}
			}
		}
		return res;
	};
	
	auto binpow = [&](vector<vector<int>> &a, int k) {
		vector<vector<int>> res(n, vector<int> (n));
		for (int i = 0; i < n; i++) {
			res[i][i] = 1;
		}
		while(k) {
			if (k & 1) {
				res = multiply(res, a);
			}
			a = multiply(a, a);
			k >>= 1;
		}
		return res;
	};
	v = binpow(v, k);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			add_self(sum, v[i][j]);
		}
	}
	cout << sum << endl;
}

int32_t main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t = 1;
	// cin >> t;
	for (int i = 0; i < t; i++) {
	    solve();
	}
}