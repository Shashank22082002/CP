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


-----------------
-----------------
## Lazy Segment Tree: Concepts & Patterns

## Overview

A **Lazy Segment Tree** is a data structure that efficiently handles range queries and range updates by deferring updates to child nodes until necessary, thus optimizing performance.

- **Time Complexity**:
    - **Build**: O(n)
    - **Update**: O(log n)
    - **Query**: O(log n)

## Core Concepts

### 1. Node Structure

Each node represents a segment (interval) of the array and stores information pertinent to the problem, such as sum, maximum, minimum, etc.

### 2. Lazy Propagation

Lazy propagation involves postponing updates to child nodes until they're needed, reducing unnecessary computations.

## Key Operations

### 1. `combine(a, b)`

Merges the results of two child nodes to form the parent node's value.

```cpp
auto combine = [](int a, int b) {
    return std::max(a, b); // Example: for range maximum query
};
```

### 2. `apply_lazy(node, lazy_value, l, r)`

Applies the pending update (`lazy_value`) to the current node covering the range `[l, r]`.

```cpp
auto apply_lazy = [](int &node, int lazy_value, int l, int r) {
    node += (r - l + 1) * lazy_value; // Example: for range addition
};

```

### 3. `merge_lazy(existing_lazy, new_lazy)`

Combines two lazy updates into a single update to be applied later.

```cpp
auto merge_lazy = [](int existing_lazy, int new_lazy) {
    return existing_lazy + new_lazy; // Example: for range addition
};

```

## Push and Pull Operations

### Push

The **push** operation propagates the lazy updates from a parent node to its child nodes. This ensures that all pending updates are applied before any further operations.

```cpp
void push(int node, int l, int r) {
    if (lazy[node] != 0) {
        tree[node] += (r - l + 1) * lazy[node];
        if (l != r) { // Not a leaf node
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

```

### Pull

The **pull** operation updates a parent node's value based on its child nodes. This is typically used after updates to child nodes to maintain correct information in the parent.

```cpp
void pull(int node) {
    tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
}

```

## Common Patterns

### 1. Range Addition and Sum Query

- **combine**: Sum of child nodes.
- **apply_lazy**: Add value to the node.
- **merge_lazy**: Sum of lazy values.[reddit.com](https://www.reddit.com/r/algorithms/comments/1gfku5j/are_segment_trees_with_lazy_propagation_on_avl/?utm_source=chatgpt.com)[reddit.com+2codeforces.com+2medium.com+2](https://codeforces.com/blog/entry/112890?utm_source=chatgpt.com)

### 2. Range Assignment and Sum Query

- **combine**: Sum of child nodes.
- **apply_lazy**: Set node to value * segment length.
- **merge_lazy**: New assignment overrides previous.

### 3. Range Multiplication and Addition with Sum Query

- **combine**: Sum of child nodes modulo MOD.
- **apply_lazy**: Apply multiplication and addition.
- **merge_lazy**: Combine multipliers and addends appropriately.[cp-algorithms.com+1codeforces.com+1](https://cp-algorithms.com/data_structures/segment_tree.html?utm_source=chatgpt.com)

## Practice Problems

1. **Sum of Squares with Segment Tree**
    - **Platform**: SPOJ - SEGSQRSS
    - **Description**: Compute the sum of squares over a range with increment and assignment updates.
2. **Range Multiplication and Addition Updates with Sum Queries**
    - **Platform**: Codeforces Blog on Multiplication and Addition Updates
    - **Description**: Perform range multiplication and addition updates, and compute the sum over a range modulo MOD.
3. **Range Maximum Query with Assignment and Conditional Updates**
    - **Platform**: DMOJ Segment Tree Practice
    - **Description**: Perform assignment and conditional updates on a range, and query the maximum value in a range.
4. **Affine Range Updates and Sum Queries**
    - **Platform**: Library Checker - Range Affine Range Sum
    - **Description**: Apply affine transformations to a range and compute the sum over a range modulo MOD.
5. **Historic Sum of Squares**
    - **Platform**: Eolymp - Sum of Squares with Segment Tree
    - **Description**: Compute the sum of squares over a range with increment updates.

Some Problems that were solved
- https://www.spoj.com/problems/SEGSQRSS/
- https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/description/
- https://judge.yosupo.jp/problem/range_affine_range_sum

Problems That can be solved while revising
- https://dmoj.ca/problem/stp3


## POWERFUL TEMPLATE
```cpp
template<typename T, typename U>
class LazySegTree {
private:
    int n;
    vector<T> st;
    vector<U> lazy;
    T SID; // Segment identity (e.g., 0 for sum, INF for min)
    U LID; // Lazy identity (e.g., 0 for add, -1 for no-op)

    function<T(T, T)> combine;                       // Combine two segments
    function<void(T&, U, int, int)> apply_update;    // Apply lazy update to segment
    function<U(U, U)> merge_lazy;                    // Merge two lazy values

    void build(int node, int l, int r, const vector<T>& a) {
        if (l == r) {
            st[node] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * node + 1, l, m, a);
            build(2 * node + 2, m + 1, r, a);
            pull(node);
        }
    }

    void push(int node, int l, int r) {
        if (lazy[node] != LID) {
            apply_update(st[node], lazy[node], l, r);
            if (l != r) {
                lazy[2 * node + 1] = merge_lazy(lazy[2 * node + 1], lazy[node]);
                lazy[2 * node + 2] = merge_lazy(lazy[2 * node + 2], lazy[node]);
            }
            lazy[node] = LID;
        }
    }

    void pull(int node) {
        st[node] = combine(st[2 * node + 1], st[2 * node + 2]);
    }

    void update(int node, int l, int r, int ql, int qr, U val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] = merge_lazy(lazy[node], val);
            push(node, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(2 * node + 1, l, m, ql, qr, val);
        update(2 * node + 2, m + 1, r, ql, qr, val);
        pull(node);
    }

    T query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return SID;
        if (ql <= l && r <= qr) return st[node];
        int m = (l + r) / 2;
        return combine(
            query(2 * node + 1, l, m, ql, qr),
            query(2 * node + 2, m + 1, r, ql, qr)
        );
    }

public:
    LazySegTree(int _n, T _SID, U _LID,
                function<T(T, T)> _combine,
                function<void(T&, U, int, int)> _apply_update,
                function<U(U, U)> _merge_lazy)
        : n(_n), SID(_SID), LID(_LID),
          combine(_combine), apply_update(_apply_update), merge_lazy(_merge_lazy)
    {
        st.assign(4 * n, SID);
        lazy.assign(4 * n, LID);
    }

    void build(const vector<T>& a) {
        build(0, 0, n - 1, a);
    }

    void update(int l, int r, U val) {
        update(0, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};
```

```CPP
template<typename T>
class SegTree {
private:
    int n;
    vector<T> st;
    T SID; // Segment identity (e.g., 0 for sum, INF for min/max)

    function<T(T, T)> combine; // Combines two segments (e.g., sum, min, max)

    void build(int node, int l, int r, const vector<T>& a) {
        if (l == r) {
            st[node] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * node + 1, l, m, a);
            build(2 * node + 2, m + 1, r, a);
            pull(node);
        }
    }

    void pull(int node) {
        st[node] = combine(st[2 * node + 1], st[2 * node + 2]);
    }

    void update(int node, int l, int r, int pos, T val) {
        if (l == r) {
            st[node] = val;
        } else {
            int m = (l + r) / 2;
            if (pos <= m)
                update(2 * node + 1, l, m, pos, val);
            else
                update(2 * node + 2, m + 1, r, pos, val);
            pull(node);
        }
    }

    T query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return SID;
        if (ql <= l && r <= qr) return st[node];
        int m = (l + r) / 2;
        return combine(
            query(2 * node + 1, l, m, ql, qr),
            query(2 * node + 2, m + 1, r, ql, qr)
        );
    }

public:
    SegTree(int _n, T _SID, function<T(T, T)> _combine)
        : n(_n), SID(_SID), combine(_combine)
    {
        st.assign(4 * n, SID);
    }

    void build(const vector<T>& a) {
        build(0, 0, n - 1, a);
    }

    void update(int pos, T val) {
        update(0, 0, n - 1, pos, val);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};
```