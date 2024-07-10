1. |A - B| = Max(A - B, B - A) -- P1 problem;

2. Optimisations :

        a. Prefix sums on rows/columns/diagonals. (p1 problem). Some others as well in Atcoder DP.

        b. Order of loop-evaluation.
        What is independent of a state calculate it separately and maybe store it.. Eg consider the problem : 
        Given a string, Find minimum number of changes to partition string in k palindromes.
        If we see it there are 2 states = [i][k]. We can define dp[i][j] as minimum changes to partition string [0..i] in j palindromes, and calculate
        dp[i][j] = min(dp[i - x][j - 1] + changes(i - x + 1, i))
        changes(i - x + 1, i) is the minimum number of changes to be done on substring. This will take O(n) time here. Overall will be O(n * k * n * n) time.
        See that "changes" function doesnot requires 'k'. It doesn't depends on that. We can have separate pal[i][j] = changes[i][j], that will store min changes for substring [i .. j]
        This can be easily done by brute forcing in O(n * n * n);
        So from O(n^3 * k) we changed complexity to O(n^3) + O(n^2 * k).
        Eg Problem : https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/

        c. Sqrt decomposition -- 
        In many cases, if a state is high, we can breakdown it in two cases, usually in one case dp works and and other case brute force works
        Eg problem : https://codeforces.com/contest/1921/problem/F
        
        d. Push dp -- 
        Updating future values.. 
         A useful tip is seek what values would be needed in the immediate next iteration and try updating the correct values for them. Here for eg, for computing dpmax[i][j + 1], we would need suffMax[i][j + 1], so I updated just that value in the current iteration(i, j).
         https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/solutions/4856083/generic-approach-to-selection-of-subarrays-dps-tabulation-o-n-k/
         
3. DP on Ranges : 

        - From operation on index we need to think of operation on a range. 
        - Mostly happens when the operation expands birectionally from an index. Like modifying neighbours.
        - Just Iterate on the range then.
        - Problem : https://codeforces.com/contest/1969/problem/C



