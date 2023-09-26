#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1E18;
ll a[401], psum[402];
ll f(int i, int j) {
    ll ans = INF;
    cout << "enterring " << i << " " << j << endl;
    if(j - i == 1) {
        cout << "leaving early " << i << ' ' << j << " " << a[i] << endl;
        return a[i];
    }
    for(int k = i + 1; k < j; k++) {
        ans = min(ans, f(i, k) + f(k, j) + psum[j+1] - psum[i]);
    }
    cout << "leaving " << i << ' ' << j << " " << ans << endl;
    return ans;
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        psum[i + 1] = psum[i] + a[i]; 
    }
    cout << f(0, n) << endl; 
    return 0;
}