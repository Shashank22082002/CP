// https://codeforces.com/contest/1899/problem/G
// first one of the same concept solved on cf
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;  
#define pb push_back
//#define mp make_pair
#define gri greater<int>
#define cnl(x) cout << x << endl
#define csp(x) cout << x << " "
#define read(x) cin >> x
#define all(v) v.begin(), v.end()

// #define pbds tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define fr(i, a, b) for (int i = a; i < b; i++) 
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
#define showVVI(arr)           \
{                              \
    for (auto &vvv : arr)      \
    {                          \
        for (auto &xxxx : vvv) \
            csp(xxxx);         \
        cout << endl;          \
    }                          \
}
#define show2d(n, m, arr)           \
{                                   \
    fr(i, 0, n)                     \
    {                               \
        fr(j, 0, m) csp(arr[i][j]); \
        cout << endl;               \
    }                               \
}

#define intt int32_t
// #define int long long
#define endl '\n'
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vpi;
typedef vector<vi> vvi;


const int N = 1e5+10;
int mod = 1e9+7;
const int INF = 1e9+7;

vector<vector<int>> g;
vector<int> in, out, p;
int tim, n;

vector<vector<int>> seg;
vector<int> a;

//build merge sort tree
void build(int node,int l,int r){
    //if range length is 1 there's only one element to add and no children
    if (l==r){
        seg[node].push_back(a[l]);
        return;
    }int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    int i=0,j=0;
    // use two pointers to merge the two vectors in O(r-l+1)
    while (i<seg[node*2].size() && j<seg[node*2+1].size()){
        if (seg[node*2][i]<seg[node*2+1][j]) seg[node].push_back(seg[node*2][i++]);
        else seg[node].push_back(seg[node*2+1][j++]);
    }
    while (i<seg[node*2].size()) seg[node].push_back(seg[node*2][i++]);
    while (j<seg[node*2+1].size()) seg[node].push_back(seg[node*2+1][j++]);
    return;
}
//query
int query(int node,int l,int r,int lx,int rx,int x){
    //if outside -> 0
    if (l>rx || r<lx) return 0;
    //if inside do binary search
    if (l>=lx && r<=rx){
        int L=0,R=seg[node].size()-1,mid,ans=0;
        while (L<=R){
            mid=(L+R)/2;
            if (seg[node][mid]<x){
                ans=mid+1;
                L=mid+1;
            }else R=mid-1;
        }return ans;
    }
    int mid=(l+r)/2;
    return query(node*2,l,mid,lx,rx,x)+query(node*2+1,mid+1,r,lx,rx,x);
}

int answer(int l, int r, int x) {
    int t1 = in[x];
    int t2 = out[x];
    int q1 = query(1, 1, n, l, r, t1);
    int q2 = query(1, 1, n, l, r, t2 + 1);
    if (q2 - q1 > 0)
        return 1;
    else
        return 0;
}

void euler_tour(int u, int p = 0) {
    in[u] = ++tim;
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        euler_tour(v, u);
    }
    out[u] = tim;
}

void solve() {
    int u, v, q, l, r, x;
    cin >> n >> q;
    g = vector<vector<int>> (n + 1);
    seg = vector<vector<int>> (4 * n + 5);
    a = p = in = out = vector<int> (n + 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    euler_tour(1);
    for (int i = 1; i <= n; i++) {
        a[i] = in[p[i]];
    }
    build(1, 1, n);
    for (int i = 0; i < q; i++) {
        cin >> l >> r >> x;
        if (answer(l, r, x))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}


intt main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(numeric_limits<double>::max_digits10);
    int t = 1;
    cin >> t;
    fr(i,1,t+1) {
        solve();
    } 
    return 0;

}
