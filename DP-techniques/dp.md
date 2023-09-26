# SOME ESSENTIAL DP TRICKS
### 1. How to print answer in dp ?? 
Always try using tabulated dp when printing answer is required.

The way is to store the answer for each state of the dp --> when the value gets updated, update the stored answer as well.

To traverse store the parents, from which current state is getting updated.. remember always in a dp a unique previous state updates the current state which can be stored :)

 CODE SNIPPET DEPICTING THE WAY : 
 https://codeforces.com/contest/1714/problem/D

```
vector<int> dp(l+1, INF), ans(l+1, -1), par(l+1, -1);
        dp[0] = 0;
        for(int i = 1; i <= l; i++) {
            for(int j = 0; j < n; j++) {
                int sz = v[j].size();
                if(i - sz < 0) continue;
                if(t.substr(i-sz, sz) != v[j]) continue;
                int mini = INF;
                int newP = -1;
                for(int k = i - sz; k < i; k++) {
                    if(mini > dp[k]) {
                        mini = dp[k];
                        newP = k;
                    }
                }
                if(dp[i] > mini + 1) {
                    dp[i] = mini + 1;
                    ans[i] = j;
                    par[i] = newP;
                }
            }
        }
```

### 2. Matrix Expo is easy
```
auto multiply = [&](vector<vector<int>> &a, vector<vector<int>> &b) -> vector<vector<int>> {
		vector<vector<int>> res(n, vector<int> (n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					add_self(res[i][j], a[i][k] * b[k][j] % MOD);
				}
			}
		}
		return res;
	};
	
	auto binpow = [&](vector<vector<int>> &a, int k) {
		vector<vector<int>> res(n, vector<int> (n));
		for (int i = 0; i < n; i++) {
			res[i][i] = 1;
		}
		while(k) {
			if (k & 1) {
				res = multiply(res, a);
			}
			a = multiply(a, a);
			k >>= 1;
		}
		return res;
	};
```

### Expectation Calculation Problems : 
1. Judiciously define the random variable :
	
	Example : 
	https://codeforces.com/contest/1753/problem/C

	Here We cannot directly apply linearity. Think of going to final state in units of 1. That is reducing prefix ones from j --> j - 1 --> j - 2... --> 0
	This can be done and calculated easily..
	