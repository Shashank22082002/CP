## Next Occurance Concpet.
This essentially involves precomputing even while answering queries in an almost brute force way, optimising complexity.

Remeber it when you need to sweep out someting in intervals, and asked to answer query for whole array(or the queried part).

<b>Assume the following problem  
You have a binary string of length N consisting of only 1's. In one query (l, r). You convert all numbers in range [l.. r] to 0. Find count of 1's in the string after every query. </b>

<i>
Sol : We can maintain a vector v s.t. v[i] gives index of next occurance of 1. Initially v[i] = i + 1;

After every query we loop from l .. r, using v (next index is v[curr idx]), make it 0 and set v[curr idx] to r + 1.

</i>

Things we can store -- 

    Next start of a interval
    Next index of a value (1/0 ..)
    Next greater element ...

Problem(Learned concept from here) : https://codedrills.io/contests/icpc-algoqueen-2023-prelims/problems/query-and-xor

We need to make a bit 0 from l .. r. See query_xor.cpp
Another solution is using the fact -- (A ^ B) & C = (A & C) ^ (B & C) (Distributive property of and)
Due to this we can use a lazy segtree.

## MAXIMUM SUM QUERIES

Seems like seen this problem a lot before but never solved it efficiently..
https://leetcode.com/problems/maximum-sum-queries/description/

PROBLEM : GIVEN TWO ARRAYS A, B. ANSWER Q QUERIES OF THE FORM (X, Y). FOR EACH QUERY FIND AN AI >= X, AND BI >= Y SUCH THAT XI + YI IS MAXIMUM.

Techinque -- "Coordinate Compression"
Sort in X.
consider two points x1, y1 and x2, y2. If x2 >= x1 and y2 >= y1, (x1, y1) is a useless point..
Sort on x, now for any point x2 > x1.. and y2 < y1 otherwise (x1, y1) is a useless point.
Do compression of points along y in this way.. using monotonic stack


