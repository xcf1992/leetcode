/*
416. Partition Equal Subset Sum
https://leetcode.com/problems/partition-equal-subset-sum/

Given a non-empty array containing only positive integers,
find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.

Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
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
This problem is essentially let us to find whether there are several numbers in a set which are able to sum to a specific value
(in this problem, the value is sum/2).

Actually, this is a 0/1 knapsack problem, for each number, we can pick it or not.
Let us assume dp[i][j] means whether the specific sum j can be gotten from the first i numbers.
If we can pick such a series of numbers from 0-i whose sum is j, dp[i][j] is true, otherwise it is false.

Base case: dp[0][0] is true; (zero number consists of sum 0 is true)

Transition function: For each number,
if we don't pick it, dp[i][j] = dp[i-1][j],
which means if the first i-1 elements has made it to j,
dp[i][j] would also make it to j (we can just ignore nums[i]).

If we pick nums[i]. dp[i][j] = dp[i-1][j-nums[i]],
which represents that j is composed of the current value nums[i] and the remaining composed of other previous numbers.
Thus, the transition function is dp[i][j] = dp[i-1][j] or dp[i-1][j-nums[i]]

talking is cheap:
*/
class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) {
            return false;
        }

        int target = sum / 2;
        vector<int> dp(target + 1, false);
        dp[0] = true;
        for (int num: nums) {
            for (int i = target; i >= num; i--) {
                dp[i] |= dp[i - num];
            }
        }
        return dp[target];
    }
};