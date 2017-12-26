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

        if (S > sum || S < -sum || (S + sum) % 2 == 1) {
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