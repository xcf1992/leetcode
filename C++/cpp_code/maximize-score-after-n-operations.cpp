/*
1799. Maximize Score After N Operations
https://leetcode.com/problems/maximize-score-after-n-operations/

You are given nums, an array of positive integers of size 2 * n.
You must perform n operations on this array.

In the ith operation (1-indexed), you will:
Choose two elements, x and y.
Receive a score of i * gcd(x, y).
Remove x and y from nums.
Return the maximum score you can receive after performing n operations.
The function gcd(x, y) is the greatest common divisor of x and y.

Example 1:
Input: nums = [1,2]
Output: 1
Explanation: The optimal choice of operations is:
(1 * gcd(1, 2)) = 1
Example 2:
Input: nums = [3,4,6,8]
Output: 11
Explanation: The optimal choice of operations is:
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
Example 3:
Input: nums = [1,2,3,4,5,6]
Output: 14
Explanation: The optimal choice of operations is:
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14

Constraints:
1 <= n <= 7
nums.length == 2 * n
1 <= nums[i] <= 106
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& A) {
        int N = A.size();
        vector<int> dp(1 << N);
        for (int m = 3; m < (1 << N); ++m) {
            // `m` is a binary mask representation of the elements in the subset
            int cnt = __builtin_popcount(m);
            if (cnt % 2) {
                continue;  // if there are even number of elements in this subset, skip
            }

            vector<int> b;  // indexes of elements in this subset
            for (int i = 0; i < 20; ++i) {
                if (m >> i & 1)
                    b.push_back(i);  // `m` is bit 1 at position `i`, which means that `A[i]` is in the current subset
            }

            for (int i = 0; i < b.size(); ++i) {
                for (int j = i + 1; j < b.size(); ++j) {
                    // use different pairs as the last operation on this subset
                    int next = m & ~(1 << b[i]) & ~(1 << b[j]);
                    // `next` represents the subset after removing `A[b[i]]` and `A[b[j]]` from subset `m`
                    dp[m] = max(dp[m], cnt / 2 * gcd(A[b[i]], A[b[j]]) + dp[next]);
                    // cnt / 2 * gcd(A[b[i]], A[b[j]]) is the score we get in the last operation. dp[next] is the
                    // maximum score we can get on the subset `next.
                }
            }
        }
        return dp.back();
    }
};