## EULER TOUR OF A TREE TECHNIQUE
-> Flattening a tree into an array to easily query and update subtrees.

-> Using in and out times for a dfs, we can get a <b>contiguous range</b> of numbers assigned to a subtree of any vertex
```
void dfs(int u, int p) {
    in[u] = ++timer;
    for (auto &v: g[u]) {
        if (v == p)
            continue;
        dfs(v, u);
    }
    out[u] = timer;
}
```

or for better visualisation of the tour use this one
```
void dfs(int u, int p) {
    euler.push_back(u); // **
    in[u] = ++timer;
    for (auto &v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    out[u] = ++timer;
    euler.push_back(u);
}

We generally can store different properties in euler tour array, for eg for computing distance between two nodes we can store edge weights, (pos and neg)

```
-> Between any two occurances of a vertex, all vertices in the subtree comes twice.

PROBLEM -- DISTINCT COLORS : https://cses.fi/problemset/task/1139

Concepts to learn

1. Array compression -- quite easy actually
    ```
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        mp[c[i]]; // insert in a map
    }
    int sz = 0;
    for (auto &it: mp)
        it.second = ++sz;
    // mp[c[i]] gives compressed value for c[i]
    ```

2. Euler tour technique -- flatten the tree. Problem reduces to finding distict values in a range now.

3. No of Distinct values in a range queries :

    Using Range sum query -- works when queries have to be answered offline and there are no updates.. 

    a. Lets say color values are stored in col, and all queries are stored in qs : {r, l, idx};

    b. sort qs on r. Consider an array RI, which stores rightmost index of the color
    RI[c] = rightmost index of color 'c' found so far. Initially all values are -1. Also have a fenwick tree(ft) of size of col, that will tell distinct colors till now

    c. Start traversing on col array. Lets say current color is col[i]. 

    If RI[col[i]] is -1, update RI[col[i]]  to i, and also update ft[i] = 1. Implying a different color found

    If RI[col[i]] is not -1, then update ft[RI[col[i]]] to 0, ft[i] = 1 and RI[col[i]] to i, That is updating Rightmost index of col[i] to i.

    d. Now if i is right end of current interval then store the answer to the query as sum(l .. r) in ft, and update curr.

    ```
    int curr = 0;
    for (int i = 1; i <= timer; i++) {
        int col = euler[i];
        if (RI[col] == -1) {
            RI[col] = i;
            ft.add(i, 1);
        } else {
            ft.add(RI[col], -1);
            RI[col] = i;
            ft.add(i, 1); 
        }
        if (qs[curr][0] == i) {
            ans[qs[curr][2]] = ft.getSum(qs[curr][1], i);
            curr++;
        }
    }
    ```

4. Small to Large Merging :
    Key Idea -- on merging small sets into bigger, a element can moved from one set to another logN times.
    On every movement set which moves atleast doubles in size.

PROBLEM -- LEVEL ANCESTORS (Finding Kth Ancestor) --> Binary lifting.

PROBLEM -- LEVEL DESCENDENTS (Finding No. of descendents of depth k) 

Solve using euler tour. Store intimes of all vertices on depth d in a vector. For a subtree we have a range of values, you need to find number of values of depth d that lie in this range, which can now be done using lower bounds.



## DIAMETER OF TREE
1. Diameter of a tree is simply
    <h3> Diameter = max(dis(u, v)) </h3>
    
2. There might be more than one diameter in a tree.
3. The ends of a diameter must be leaf nodes.
4. <b>Theorem</b> - Let d be the node such that dis(u, d) is the maximum for any u, then d is one of the ends of a diameter. In other words, <b>
Let L, R be two ends of a diameter, Then max(dis(u, v)) = max(dis(u, L), dis(u, R)). </b>
        
    ```
    Proof (using contradiction) :
    Let A, B be two nodes such that
    dis(A, B) > max(dis(A, L), dis(A, R))
    Let a be the LCA(L, R) considering tree rooted at A, and b be the LCA(L, R) considering tree rooted at B. *Let L, a, b, R occur in this order in the diameter.

    Then, d(A,a)+d(a,b)+d(b,B) ≥ d(A,B) > d(A,R) = d(A,a)+d(a,R), so 
    d(a,b)+d(b,B) > d(a,R), thus 
    d(L,B)=d(L,a)+d(a,b)+d(b,B)>d(L,a)+d(a,R)=d(L,R), which is a contradiction.
    * Note that for any two vertices a, b LCA(a, b) always lies on path from a -- b irrespective of where the tree is rooted.
    ```
5. Hence to find diameter, find most distant node to any node, then find most distant node to this node (use bfs preferably twice).

