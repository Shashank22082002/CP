#include <bits/stdc++.h>
using namespace std;
#define intt int32_t
#define int long long
#define endl '\n'
#define all(v) v.begin(), v.end()
 
#define csp(x) cout << x << " "
#define show(arr)         \
{                         \
    for (auto &xxx : arr) \
        csp(xxx);         \
    cout << endl;         \
}
 
#define showVpi(arr)                     \
{                                        \
    for(auto &it : arr)                  \
    cout<<it.first<<" "<<it.second<<endl;\
}    
 
typedef long long ll;
const int MOD = 998244353;
const int INF = 1E13;
 
bool canCombine(vector<int> &node1, vector<int> &node2) {
    // check if can merge node1 and node2
    // assuming l2 >= l1 => 
    int l1 = node1[3], r1 = node1[2], a1 = node1[1], b1 = node1[0];
    int l2 = node2[3], r2 = node2[2], a2 = node2[1], b2 = node2[0];
    // (a1, b1) and (l2, r2) are intersecting
    if(l2 > b1)
        return false;
    return true;
}
 
vector<int> combine(vector<int> &node1, vector<int> &node2) {
    int l1 = node1[3], r1 = node1[2], a1 = node1[1], b1 = node1[0];
    int l2 = node2[3], r2 = node2[2], a2 = node2[1], b2 = node2[0];
    return {max(b1, b2), min(a1, a2), max(r1, r2), min(l1, l2)};
}
 
void solve() {
    int n;
    cin >> n;
    int l, r, a, b;
    vector<int> dp(n+1, -1);
    vector<vector<int>> v;
    // dp[i] stores maximum far I can go, if start from ith segment
    for(int i = 0; i < n; i++) {
        cin >> l >> r >> a >> b;
        v.push_back({b, a, r, l});
    }
    vector<pair<int, int>> L;
    sort(all(v), [](const vector<int> &a, const vector<int> &b){
        return a[3] < b[3]; 
    });
    // sort(all(v));
    // for(auto &it: v)
    //     show(it);
    for(int i = 0; i < n;) {
        vector<int> temp = v[i];
        int j = i;
        while(j < n && canCombine(temp, v[j])) {
            temp = combine(temp, v[j]);
            j++;
        }
        for(int k = i; k < j; k++) {
            dp[k] = temp[0];
        }
        L.push_back({temp[3], i});
        i = j;
    }
    sort(all(L));
    int q, x;
    cin >> q;
    while(q--) {
        cin >> x;
        pair<int, int> p = {x+1, 0};
        auto it = lower_bound(all(L), p);
        if(it == L.begin()) {
            cout << x << " ";
            continue;
        }
        --it;
        cout << max(x, dp[it->second]) << " ";
    }
    cout << endl;
}
 
intt main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(numeric_limits<double>::max_digits10);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++)
    solve();
    return 0;
}