/*
1043. Partition Array for Maximum Sum
https://leetcode.com/problems/partition-array-for-maximum-sum/

Given an integer array A,
you partition the array into (contiguous) subarrays of length at most K.

After partitioning,
each subarray has their values changed to become the maximum value of that subarray.
Return the largest sum of the given array after partitioning.

Example 1:
Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]

Note:
1 <= K <= A.length <= 500
0 <= A[i] <= 10^6
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
#include <set>
#include <numeric>
using namespace std;
/*
dp[i] record the maximum sum we can get considering A[0] ~ A[i]
To get dp[i], we will try to change k last numbers separately to the maximum of them,
where k = 1 to k = K.
*/
class Solution {
public:
    int maxSumAfterPartitioning(vector<int> &A, int K) {
        int n = A.size();
        if (n == 0) {
            return 0;
        }

        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            int maxNum = A[i];
            for (int k = 1; k <= K and i
            -k + 1 >= 0;
            ++k
            )
            {
                // we pick A[i - k + 1] to A[i] this k elements as a group
                maxNum = max(maxNum, A[i - k + 1]);
                dp[i] = max(dp[i], (i - k >= 0 ? dp[i - k] : 0) + k * maxNum);
            }
        }
        return dp[n - 1];
    }
};