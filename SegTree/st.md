## Segtrees

1. Querying : Convinient way of implementation -- intuitive
```
int query(int node, int l, int r, int p, int q) {
    if (p == l && q == r) {
        return st[node];
    }
    int mid = (l + r) / 2;
    if (p > mid) {
        return query(2*node + 2, mid + 1, r, p, q);
    }
    if (q <= mid) {
        return query(2*node + 1, l, mid, p, q);
    }
    int x1 = query(2*node + 1, l, mid, p, mid);
    int x2 = query(2*node + 2, mid + 1, r, mid + 1, q);
    return x1 + x2;
}

```

2. A recurring pattern.. Creating array of 1st occurances of index.
```
for (int i = 0; i < m; i++) {
        cin >> l >> r;
        --l, --r;
        while (true) {
            auto it = sx.lower_bound(l);
            if (it == sx.end() || *it > r) break;
            idx.push_back(*it);
            sx.erase(it);
        }
    }
```

3. Most problems, we need to find indexes on which querying have to be done... Think constructively helps

4. Take care of the identity element..
