/*
494. Target Sum
https://leetcode.com/problems/target-sum/

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S.
Now you have 2 symbols + and -.
For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
There are 5 ways to assign symbols to make the sum of nums be target 3.

Note:
The length of the given array is positive and will not exceed 20.
The sum of elements in the given array will not exceed 1000.
Your output answer is guaranteed to be fitted in a 32-bit integer.
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;
/*
The original problem statement is equivalent to:
Find a subset of nums that need to be positive, and the rest of them negative, such that the sum is equal to target

Let P be the positive subset and N be the negative subset
For example:
Given nums = [1, 2, 3, 4, 5] and target = 3 then one possible solution is +1-2+3-4+5 = 3
Here positive subset is P = [1, 3, 5] and negative subset is N = [2, 4]

Then let's see how this can be converted to a subset sum problem:

                  sum(P) - sum(N) = target
sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
                       2 * sum(P) = target + sum(nums)
So the original problem has been converted to a subset sum problem as follows:
Find a subset P of nums such that sum(P) = (target + sum(nums)) / 2
*/
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (S > sum or S < -sum or (S + sum) % 2 == 1) {
            return 0;
        }

        int newS = (sum + S) / 2;
        vector<int> dp(newS + 1, 0);
        dp[0] = 1;
        for (int num : nums) {
            for (int i = newS; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        return dp[newS];
    }
};

/*
this is a classic knapsack problem
in knapsack, we decide whether we choose this element or not
in this question, we decide whether we add this element or minus it

So start with a two dimensional array dp[i][j] which means the number of ways for first i-th element to reach a sum j

we can easily observe that dp[i][j] = dp[i-1][j+nums[i]] + dp[i-1][j-nums[i],

Another part which is quite confusing is return value, here we return dp[sum+S], why is that?
because dp's range starts from -sum --> 0 --> +sum
so we need to add sum first, then the total starts from 0, then we add S

Actually most of Sum problems can be treated as knapsack problem, hope it helps
*/
class Solution1 {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (S > sum or S < -sum) {
            return 0;
        }

        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * sum + 1));
        dp[0][sum] = 1;
        for (int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for (int j = 0; j <= 2 * sum; j++) {
                if (j + num <= 2 * sum) {
                    dp[i][j] += dp[i - 1][j + num];
                }
                if (j - num >= 0) {
                    dp[i][j] += dp[i - 1][j - num];
                }
            }
        }
        return dp[n][sum + S];
    }
};