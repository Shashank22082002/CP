## Facts : 
1. LCM/GCD is an associative operation -- lcm(a, b, c) = lcm(lcm(a, b), c) = lcm(a, lcm(b, c))
2. 1E5th prime is not as big you think -- its 1299709. So 2E6 may be a good bound to find first 1E5 primes
// may think like NlogN th number is Nth prime
3. If LCM(a, b) = c and a < c and b < c(a is not some multiple of b or vice versa), then a/b must have atleast 2 different prime factors. Or a, b can't be expressed as p^k, where p is some prime.
(https://www.codechef.com/problems/FIZZBUZZ2308)

4. Let a < b and c = gcd(a, b). Then either c == a or c < a/2.
This fact is used to prove that gcd(a, b) can be calculated in log(a) steps.
Infact this complexity is achieved when a and b are consecutive fibonacci numbers, gcd(Fn, Fn+1) takes n steps to be computed.

5. Suppose you have an array of n numbers. Start with a number x <= 10^9. Take gcd with any of n numbers repeatedly (i.e x = gcd(x, a)). Then x can have atmost log(10^9) distinct values. (Using above fact).
Problem based on this idea -- https://www.codechef.com/problems/KSIZEGCD

    This idea coupled with binary search to find first changing values -- for every l find r's where gcd changes, for fixed l there can be atmost 30 such rs. (Problem setting idea -- find maximum value of (r - l + 1)gcd(l .. r) over the array.)

    UPD: Another problem on this idea -- https://codeforces.com/problemset/problem/1632/D


6. Computing sigma(k * floor(N/k)) for all k from 1 .. N. (In better than O(N) ofc)
    
    <b> IDEA -- N/k takes atmost 2 * sqrt(N) distinct values for variable k. </b>

    Lets vary k from 1 .. N

    Case 1 : k lies in 1 ... sqrt(N). Since there are sqrt(N) values of k, there are atmost sqrt(N) values of N/k.

    Case 2 : K lies in sqrt(N) + 1 ... N. Then N/k <= sqrt(N). Hence again there are atmost sqrt(N) values of N/k. 
    
    Now to compute this series we can find intervals of k where value of N/k remains same.
    Lets say beginning of an interval is at k = l. Hence the value is N/l. Next starting interval will be at k = N/(N/l) + 1 (If v = N/l, max k at which N/k is still v is N/v -- Think a bit N/v is always greater than l, and its the largest l where N/l is still v).

    Here we encounter a very important property -- 
    If floor (N/k) = v then if floor (N/v) = k' then k' is the largest k at which N/k' still remains v.

    Insight -- If N/k = v, N lies from [v * k -- v * k + k - 1]

    See that as k increases k - 1/v can give a positive result, so that we get a range for k.
    Wehn k is small, there are only single k's for a value of N/k.

    <B>
    <I>
    <H3>
    Very Important Property on Fractions:

    IF X/K=Z,  then x lies in [kz ,  kz+z−1]  

    IF X/K=Z,  then k lies in [floor(x/z),   ceil((x+1)/(z+1))]  or [floor(x/z),  floor(x/(z+1)))

    IF X/K=Z,  then there are O(sqrt(X))  values of Z…for K in [1, X].
    These values( lets say z)are repeating for z in [1, sqrt(X)], rest distinct values are just Z/z, where z is [1, sqrt(X)]. 

    −−So one can easily iterate over X/k  in this way, in just O(sqrt(X))−− 
    </H3>
    </I>
    </B>
    
    Problem -- https://cses.fi/problemset/task/1082

7. Linear sieve -- runs in O(N) time. Takes some more space. Erastothenes takes N bits to find primes till N. Linear sieve takes N bytes, since it works on spf -- smallest prime factor.

    ```
    // Linear Sieve
    vector < int > primes;
    vector < int > spf;

    void RunLinearSieve() {
    int n = N;
    spf.assign(n + 1, 0);
    spf[1] = 1;
    for(int i = 2; i < n; ++i) {
        if(!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for(int x : primes) {
            int calc = i * x;
            if(x > spf[i] || calc > n) {
                break;        
            }
            spf[calc] = x;
            }
        }
    }
    ```
8. Number of solutions of A * B == N
    General solutions -- This is same as finding number of ways to express N as a product of 2 numbers.
    Let d be a divisor of N, then one ordered pair is {d, N/d}; Hence if we find number of divisors we can have ordered solutions.
    If Number of divisors of N = D(N).
    Ordered solutions are -- D(N)
    Unordered solutions {(a, b) == (b, a)} are -- ceil(D(N)/2).

    Coprime solutions -- Find # distinct prime factors. If this count is p, 
    ordered pairs are 2^p
    unordered pairs are 2^(p - 1)

9. How to solve equations involving LCM(a, b) and GCD(a, b)
    Note if g is gcd(a, b)

    Substitute these would simplify it -- <ul>
    <li> a = gA
    <li> b = gB
    <li> LCM(a, b) = gAB
    <li> GCD(a, b) = g
    <li> GCD(A, B) = 1
    </ul>

10. Some important intermediate problems helpful in many scenarios --

    1. Finding spf -- for prime factorisation of many numbers
    O(logN) per number

    2. Finding count of divisors of all numbers -- use sieve fashion (N + N/2 + N/3 ...  ) = NlogN

    3. Finding count of unique prime factors for all numbers from 1 .. N. Use dp with spf. 

            upf[i] = upf[i/spf[i]] + (spf[i] != spf[i/spf[i]])

    4. Finding prime factorisation of a single number in O(sqrt(N)). 
    ```
        vector<pii> pf;
        while (i * i <= N)
            ct = 0;
            while (N % i == 0)
                N /= i, ct++;
            pf.push_back({i, ct})
        if (n > 1)
            pf.push_back({i, 1})
        Note this is generally better than sqrt(N) since N decreases as factors are found 
    ```
    5. Finding number of pairs of numbers with gcd i, for every i. Approach : 
        - Find for every integer, how many numbers have it as a divisor.

        - Find how many pairs have it as a common divisor.

        - Find how many pairs have it as only divisor -- iterate from largest integer, since for it count is correct.

    ```
    int maxv = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        mp[v[i]]++;
        maxv = max(maxv, v[i]);
    }
    
    vector<int> dp(maxv + 1), pairs(maxv + 1);
    for (int i = 0; i <= maxv; i++) {
        if (mp[i] == 0)
            continue;
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                dp[j] += mp[i];
                if (j * j != i)
                    dp[i/j] += mp[i];
            }
        }
    }
    for (int i = 1; i <= maxv; i++)
        pairs[i] = (dp[i] * (dp[i] - 1)) / 2;
    for (int i = maxv; i >= 1; i--) {
        for (int j = 2 * i; j <= maxv; j += i) {
            pairs[i] -= pairs[j];
        }
    }
    ```


## Divisibility / Modulus
### 1. Fermat little theorem : 

- Useful for computing a^l % M, where l is a large number, M is prime and (a, M) are coprime. (Generally a is quite small than M so this is not checked, but we should keep this in mind).

- The theorem suggests that a^M == a mod M, if M is a prime number.

- If a, M are coprime, we can also have
a^(M-1) == 1 mod M.

- writing l as x*(M - 1) + r. 
    
    - a^(M-1) == 1 mod M.

    - a^x*(M-1) + r == a^r mod M

    - <B> a^l == a^r mod M, r = a%(M - 1). </B>
- This fact can be used to compute large powers of a modulo M. only conditions being a, M are coprime and M is a prime.

- Also used to compute inverse modulo, inv(a) % M == a^(M - 2) % M.

### 2. Divisors statistics
- Express n = p1^k1 * p2^k2 * p3^k3 ... 
- Number of divisors = d(n) = (k1 + 1) * (k2 + 1) * (k3 + 1) .. (kn + 1).
[p1^0, p1^1, ... p1^k1 , total of k1 + 1 options... and so on]
- Sum of divisors =

    Prod(pi^(ki + 1) - 1)/(pi - 1).
- Product of divisors = 
    n ^ (d(n)/2).
    n ^ (d(n) - 1) / 2 * sqrt(n), if n is a perfect square.

    Read from here : 
    https://blog.codechef.com/2009/08/17/tutorial-for-problem-product-of-divisors/
