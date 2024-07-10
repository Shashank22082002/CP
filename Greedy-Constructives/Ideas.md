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

2.) Frequency array properties :
 Frequency array is array formed by considering frequencies of all distinct elements in an array.
 1. Sum of all elements in frequency array is n
 2. If minimum element is greater than sqrt(n), then overall there are less than sqrt(n) elements in it. 
 ```
 for (num : [1 .. mini])
    for (v : fre)
```
This is overall O(n) :: n is size of the array on which fre array is build complexity.

Problem : 
https://leetcode.com/problems/minimum-number-of-groups-to-create-a-valid-assignment/description/

3.) Convert a permutation into another, by swapping adjacent numbers.
Use Merge sort to find number of inversions.
Assume original permutation is mapped to [1, 2, 3 ... n]
then find what will be the mapping of the new permutation.

See this problem : https://codeforces.com/contest/1430/problem/E



