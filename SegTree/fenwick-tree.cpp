#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Fenwick {
    vector<T> a;
    int n;
    Fenwick() : a(), n(0) {}
    Fenwick(int _n) {
        n = _n;
        a = vector<T> (n, T());
    }
    void clear() {
        a = vector<T> (n, T());
    }
    void add(int p, T x) {
        for(; p < n; p += (p & (-p)))
            a[p] += x;
    }
    T get(int r) {
        T res = T();
        for(; r > 0; r -= (r & (-r)))
            res += a[r];
        return res;
    } 
    T getSum(int l, int r) {
        return get(r) - get(l - 1);
    }
};

int main() {
    vector<int> v = {0, 4, 5, 7, 8, 2, -5, 6, -2};
    Fenwick<int> f(9);
    for (int i = 1; i < 9; i++) {
        f.add(i, v[i]);
    }
    cout << f.getSum(1, 5) << endl;
    cout << f.getSum(6, 8) << endl;
    return 0;
}