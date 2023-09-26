// serious tree dp problem
// https://codeforces.com/problemset/problem/1746/D
// notice the states here.. 

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 1e9+7;

vector<vector<int>> g;
vector<int> p, s;
vector<map<int, int>> dp;
int dfs(int u, int k) {
	// distribute k among all children
	int n = (u==1)? g[u].size() : g[u].size()-1;
	if(n == 0) return k * s[u];
	if(dp[u].find(k) != dp[u].end())
		return dp[u][k];
	int k1 = k/n;
	int k2 = k%n; // k2 times ceil
	vector<pair<int, int>> vp;
	for(auto &v: g[u]) {
		if(v == p[u]) continue;
		pair<int, int> pi;
		pi.first = dfs(v, k1);
		pi.second = dfs(v, (k+n-1)/n);
		vp.push_back(pi);
	}
	assert(vp.size() == n);
	sort(vp.begin(), vp.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
		return (a.second - a.first) > (b.second - b.first);
	});
	int ans = k * s[u];
	for(int i = 0; i < n; i++) {
		if(i < k2)
			ans += vp[i].second;
		else
			ans += vp[i].first;
	}
	return dp[u][k] = ans;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	g = vector<vector<int>> (n+1);
	dp = vector<map<int, int>> (n+1);
	p = s = vector<int> (n+1);
	for(int i = 2; i <= n; i++) {
		cin >> p[i];
		g[i].push_back(p[i]);
		g[p[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	// dfs(1);
	cout << dfs(1, k) << endl;
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    solve();
}