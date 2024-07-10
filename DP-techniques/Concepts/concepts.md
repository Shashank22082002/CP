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




