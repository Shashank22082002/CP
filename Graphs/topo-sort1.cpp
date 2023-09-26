// problem -- https://codeforces.com/contest/1385/problem/E
// Easy based on concepts..
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 1e9+7;

vector<vector<int>> g;
vector<int> topo;
bool checkCycle(int u, vector<int> &vis) {
	bool found = false;
	vis[u] = 1;
	for(auto &ch: g[u]) {
		// if vis[ch] = 1 means cycle
		// if vis[ch] = 2 then continue
		if(vis[ch] == 1) {
			return true;
		}
		if(vis[ch] == 2) {
			continue;
		}
		found |= checkCycle(ch, vis);
	}
	vis[u] = 2;
	return found;
}

void dfs(int u, vector<int> &vis) {
	vis[u] = 1;
	for(auto &ch: g[u]) {
		if(vis[ch]) continue;
		dfs(ch, vis);
	}
	topo.push_back(u);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	g = vector<vector<int>> (n+1);
	topo.clear();
	int x, u, v;
	vector<pair<int, int>> edges, dir;
	for (int i = 0; i < m; i++) {
		cin >> x >> u >> v;
		if(x == 0) {
			edges.push_back({u, v});
		} else {
			dir.push_back({u, v});
			g[u].push_back(v);
		}
	}
	vector<int> vis(n+1);
	bool found = 0;
	for(int i = 1; i <= n; i++ ){
		if(vis[i] == 2) continue;
		found |= checkCycle(i, vis);
	}
	if(found) {
		cout << "NO" << endl;
		return;
	}
	map<int, int> ind;
	vis = vector<int> (n+1, 0);
	for(int i = 1; i <= n; i++ ) {
		if (vis[i]) continue;
		dfs(i, vis);
	}
	reverse(topo.begin(), topo.end());
	for(int i = 0; i < n; i++ ) {
		ind[topo[i]] = i;
	}
	
	for(auto &it: edges) {
		int x = it.first, y = it.second;
		if (ind[x] > ind[y]) {
			swap(x, y);
		}
		dir.push_back({x, y});
	}
	cout << "YES" << endl;
	for(auto &it: dir) {
		cout << it.first << " " << it.second << endl;
	}
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