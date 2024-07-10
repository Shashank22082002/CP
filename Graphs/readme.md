# Important Graph Concepts #
## Topological Ordering of Vertices ##
<ul>
<li> In almost all the problems involving Directed Acyclic graphs, looking at topological ordering of vertices makes things a lot more simpler, since there are only edges from left to right .. in a fixed direction.
</li>
<li> In other words in <b>any Directed Acyclic Graph</b>, there always exists an ordering of vertices such that all edges go in one direction.
</li>
<li>There can be multiple topo ordering possible.
</li>
<li>In Topographical sorting introducing any edges from a left vertex to a right vertex won't introduce a cycle in the graph.</li>
<li>
An observation : nodes with indegree 0 will appear first. Nodes appear in the ascending order of their indegree.
</li>
</ul>

### Two ways to find topo order -- 

### 1. USING DFS -- 

First check for existence of cycle
```
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
```

If no cycle -- topo sort can be found
```
void dfs(int u, vector<int> &vis) {
	vis[u] = 1;
	for(auto &ch: g[u]) {
		if(vis[ch]) continue;
		dfs(ch, vis);
	}
	topo.push_back(u);
}

// reverse of list gives topo sort
```
Why this works -- we go on till we there is no edge from a vertex, this vertex should come in the last.

For any vertex v, apply dfs on successors of v – append v on the list end..

### 2. Using BFS -- KAHN'S ALGO

First of all, calculate indegrees of each node.

Now push nodes having indegree 0 in your answer, as well as queue of bfs and mark them visited. 

Now as you vis through a node, assume that node is deleted from the graph. Now this will reduce the indegrees of the nodes connected to it by 1! And do so!

New nodes will be created with indegree 0 out of them only. So push them if they are so.
```
vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    vector<int> deg(V, 0);
	    for(int i = 0; i < V; i++){
	        for(auto it: adj[i])
	            deg[it]++;
	    }
	    vector<int> topo;
	    queue<int> q;
	    for(int i = 0; i < V;i++)
	    {
	        if(deg[i] == 0)
	        q.push(i);
	    }
        while(!q.empty())
        {
            int v = q.front();
            topo.push_back(v);
            q.pop();
            for(auto u: adj[v])
            {
                deg[u]--;
                if(deg[u]==0)
                q.push(u);
            }
        }
        return topo;
	}

```
If the number of elements in topo vector is Not N tells that there is a cycle, basically the degree never becomes 0 for the node, for whom the adjacent nodes are seen.

Shortest distance in a Directed Acyclic Graph can be found using Topo sort followed by bfs!


## Modelling DP problems as graphs ##
Suppose there is some problem where you have to choose to apply operations.
operations are defined in an array..

If operations have can be performed in "any order" we can use dynamic programming to solve the problem

Formally when
```
[state] ----> ith operation ----> [state 1] ----> jth operation ---> [state 2]
[state] ----> jth operation ----> [state 3] ----> ith operation ---> [state 2]
```

Here applying operations is commutative in nature..

In such cases DP technique is applicable..

However when this is not the case... We need a specific order of operations to be performed, we need to iterate on all 2^n sequences of n operations ... to solve it using DP.

In such problems generally graph algorithms can be killer way. We basically form a graph of all the possible states as nodes and the cost of going from one state to another is defined by operations..


This will have O(number of states) nodes and O(operations * number of states) edges, as for every state all operations can be done..

We can generally then use shortest path algorithms to go from one state to other..

<b>In general we can think every dp problem as graph by thinking states as nodes and transitions as edges to go from one state to other :)</b>

Some examples (plenty in leetcode) -- 

[https://codeforces.com/contest/1846/problem/G](https://codeforces.com/contest/1846/problem/G)


## Awesome dijkstra problems ##

[https://codeforces.com/problemset/problem/1725/M](https://codeforces.com/problemset/problem/1725/M)
Know whats exactly relaxation in dijkstra -- we can relax a vertex any number of times, and sometimes we might want to do this multiple times.

[Moving Both Hands](https://codeforces.com/contest/1725/problem/M) --- Shortest path, but both can move

## Adjacency matrix ##

Adjacency matrix provides several other properties other than telling about edges between individual vertices...


If M denotes the adjacency matrix:
<li> M[i][j] denotes number of direct paths from i --> j. </li>
<li> <b>M^k is denotes number of k length paths from i -- j.  </b> </li>

[Problem](https://atcoder.jp/contests/dp/tasks/dp_r)

## Suggestions
1. Use bfs to calculate distances between nodes in a graph, its better to implement than a dfs
2. Use dfs when dp has to be done, easier to visualise.
3. To find cycles in graphs, use dfs with stack -- it makes things lot simpler, also use vector as a stack. Eg: https://codeforces.com/contest/1873/problem/H

	```
	void findCycle(int u, int p, vector<int> &st) {
		vis[u] = 1;
		st.push_back(u);
		for (auto &v: g[u]) {
			if (v == p) 
				continue;
			
			if (vis[v]) {
				if (!cycle.empty()) {
					continue;
				}
				for (int i = st.size() - 1; i >= 0; i--) {
					cycle.insert(st[i]);
					if (st[i] == v)
						break;
				}
				return;
			}
			findCycle(v, u, st);
		}
		st.pop_back();
	}
 
	```
4. Path in graph -- refers to any route between two vertices maybe repeating edges and vertices(loopy ones). Trail refers to path of shortest length.

	To calculate paths use bfs as pointed earlier, its easier and cleaner.
	You might need to calculate paths with some properties. Eg odd length and even length paths. 
	In such cases, one may look vertices with some parity as state.
	for eg : one moves from {u, 0} -- {v, 1} or {u, 1} -- {v, 0} instead of u -- v. This concept was also presented earlier and quite useful.

	Eg : https://www.codechef.com/problems/FIZZBUZZ2309

