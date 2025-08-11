#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()

struct Node {
    string var;
    string expr;
    vector<pair<bool, string>> deps;
    int idx;

    Node(string var, string expr, vector<pair<bool, string>> deps, int idx) 
        : var(var), expr(expr), deps(deps), idx(idx) {};
};

void dfs(int u, vector<int> &vis, vector<int> &topo, vector<vector<int>> &g) {
    vis[u] = 1;
    for (auto &v : g[u]) {
        if (!vis[v])
            dfs(v, vis, topo, g);
    }
    topo.push_back(u);
}

bool findCycle(int u, vector<int> &vis, vector<vector<int>> &g) {
    bool found = 0;
    vis[u] = 1;
    for (auto &v : g[u]) {
        if (vis[v] == 1) {
            return true;
        } else if (vis[v] == 0) {
            found |= findCycle(v, vis, g);
        }
    }
    vis[u] = 2;
    return found;
}

void solve() {
    string sn;
    getline(cin, sn);
    // cout << sn;
    int n = stoi(sn);
    vector<string> lines(n);

    map<int, Node*> idxs;
    map<string, Node*> vars;

    auto parse = [&](string &str, int idx) {
        int sz = str.size();
        // cout << str << endl;
        string var = "", expr = "";
        for (int i = 0; i < sz; i++) {
            if (str[i] == '=') {
                var = str.substr(0, i);
                expr = str.substr(i + 2, sz - (i + 3));
                break;
            }
        }

        // cout << var << " " << expr << endl;

        vector<pair<bool, string>> deps;
        sz = expr.size();
        string literal = "";
        for (int i = 0; i < sz; i++) {
            if (expr[i] == '$') {
                if (literal.size() > 0) {
                    deps.push_back({false, literal});
                    literal = "";
                }
                // variable
                string variable = "";
                for (int j = i + 1; j < sz; j++) {
                    if (expr[j] == '$') {
                        deps.push_back({true, variable});
                        i = j;
                        break;
                    } else {
                        variable += expr[j];
                    }
                }
            } else {
                literal += expr[i];
            }
        }
        if (literal.size() > 0) {
            deps.push_back({false, literal});
        }

        Node* node = new Node(var, expr, deps, idx);
        idxs[idx] = node;
        vars[var] = node;
    };

    for (int i = 0; i < n; i++) {
        getline(cin, lines[i]);
        parse(lines[i], i);
    }

    // parse and create graph
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        auto node = idxs[i];
        for (auto &dep : node->deps) {
            if (dep.first) {
                int idx = vars[dep.second]->idx;
                g[idx].push_back(i);
            }
        }
    }

    vector<int> vis(n);

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (findCycle(i, vis, g)) {
                cout << "Cycle detected " << endl;
                cout << "-1" << endl;
                return;
            }
        }
    }

    vis = vector<int> (n);
    vector<int> topo;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, vis, topo, g);
        }
    }

    reverse(topo.begin(), topo.end());
    map<string, string> values;
    for (auto &u : topo) {
        auto node = idxs[u];
        string var = node->var;
        string final_val = "";
        for (auto &dep : node->deps) {
            if(dep.first) {
                final_val += values[dep.second];
            } else {
                final_val += dep.second;
            }
        }
        cout << var << ": " << final_val << endl;
        values[var] = final_val;
    }
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}