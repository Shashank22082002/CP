1.) Idea : Think about what you gain, and what you loose at every step. 
In problems where tradeoffs are present

https://codeforces.com/contest/1684/problem/D

Think about the final configuration.

Let say we skip k traps with some indices i1, i2, i3. .. ik (sorted)

On removing i1, we reduce total cost by
a[i1] - (n - i1) + (k - 1) == increased cost of n - i1

Similarly for i2,
a[i2] - (n - i2) + (k - 2)
.....

total cost removed will be
(sigma a[i] + i) + some fixed factor

Hence we need to just maximise the value of a[i] + i .....



