/*
974. Subarray Sums Divisible by K
Given an array A of integers,
return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

Example 1:

Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]


Note:

1 <= A.length <= 30000
-10000 <= A[i] <= 10000
2 <= K <= 10000
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;
/*
Let there be a subarray (i, j) whose sum is divisible by k
sum(i, j) = sum(0, j) - sum(0, i-1)
Sum for any subarray can be written as q*k + rem where q
is a quotient and rem is remainder
Thus,
sum(i, j) = (q1 * k + rem1) - (q2 * k + rem2)
sum(i, j) = (q1 - q2)k + rem1-rem2

We see, for sum(i, j) i.e. for sum of any subarray to be
divisible by k, the RHS should also be divisible by k.
(q1 - q2)k is obviously divisible by k, for (rem1-rem2) to
follow the same, rem1 = rem2 where
rem1 = Sum of subarray (0, j) % k
rem2 = Sum of subarray (0, i-1) % k
*/
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        vector<int> mod(K, 0);
        int curSum = 0;
        int result = 0;
        for (int i = 0; i < n; i++) {
            curSum += A[i];
            int left = ((curSum % K) + K) % K;
            result += mod[left];
            mod[left] += 1;
        }
        return result + mod[0];
    }
};
