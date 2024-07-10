#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

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

const int N = 1E6 + 100;
const int INF = 1E18;
const int MOD = 1E9 + 7;
const int M = 63;

int countSub(vector<int> arr, int n)
{
    // count[] array is used to store all sub-
    // sequences possible using that digit
    // count[] array covers all the digit
    // from 0 to 9
    int count[10] = {0};
 
    // scan each digit in arr[]
    for (int i=0; i<n; i++)
    {
        // count all possible sub-sequences by
        // the digits less than arr[i] digit
        for (int j=arr[i]-1; j>=0; j--)
            count[arr[i]] += count[j];
 
        // store sum of all sub-sequences plus
        // 1 in count[] array
        count[arr[i]]++;
    }
 
    // now sum up the all sequences possible in
    // count[] array
    int result = 0;
    for (int i=0; i<10; i++)
        result += count[i];
 
    return result;
}

vector<int> ops;
int mx = 1;
void find(int x) {
    int zs = 0;
    if (x == 2) {
        ops.push_back(1);
        return;
    } else if (x == 3) {
        ops.push_back(1);
        ops.push_back(1);
        return;
    } else if (x == 1) {
        
    }
    if (x % 2 == 0) {
        while (x % 2 == 0) {
            x /= 2;
            zs++;
        }
        find(x - 1);
        for (int i = 0; i < zs; i++) {
            ops.push_back(mx);
            mx++;
        }
        ops.push_back(1);
    } else {
        find(x >> 1LL);
        ops.push_back(mx);
        mx++;
    }
}

void solve() {
    int X;
    cin >> X;
    find(X);
    show(ops);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        solve();
    }
}