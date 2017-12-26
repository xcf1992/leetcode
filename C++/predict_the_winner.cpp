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
Given an array of scores that are non-negative integers.
 Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on.
 Each time a player picks a number, that number will not be available for the next player.
 This continues until all the scores have been chosen. The player with the maximum score wins.
DP formula:
dp(i, j) = max(sum(i, j-1) - dp(i, j-1) + nums[j], sum(i+1, j) - dp(i+1, j) + nums[i])

Because sum(i, j-1) + nums[j] = sum(i, j) = nums[i] + sum(i+1, j), the formula can be simplified to
dp(i, j) = max(sum(i, j) - dp(i, j-1), sum(i, j) - dp(i+1, j))

If we do more deduction, we can eliminate the sum(i, j) from the formula:
Instead of storing the maximum score that player 1 can get in each sub array, we can store the diff between player1 and player 2. For example: if player 1 get A, player 2 get B, we can use dp' to store A-B.

if A = dp(i, j), then B = sum(i, j) - dp(i, j)

So dp'(i, j) = dp(i, j) - ( sum(i, j) - dp(i, j) ) = 2*dp(i, j) - sum(i, j), so
2*dp(i, j) = dp'(i, j) + sum(i, j) (this will be used below)

dp'(i, j) = dp(i, j) - ( sum(i, j) - dp(i, j) ) = 2dp(i, j) - sum(i, j)
= 2 * max( sum(i, j) - dp(i, j-1), sum(i, j) - dp(i+1, j) ) - sum(i, j)
= max(sum(i, j) - 2*dp(i, j-1), sum(i, j) - 2*dp(i+1, j) )
= max(sum(i, j) - ( dp'(i, j-1) + sum(i, j-1) ), sum(i, j) - ( dp'(i+1, j) + sum(i+1, j)))
= max(sum(i, j) - sum(i, j-1) - dp'(i, j-1), sum(i, j) - sum(i+1, j) - dp'(i+1, j))
= max(nums[j] - dp'(i, j-1), nums[i] - dp'(i+1, j))

Final formula: dp(i, j) = max(nums[j] - dp(i, j-1), nums[i] - dp(i+1, j))
 */
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
        }
        for (int len = 1; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                dp[i][i + len] = max(nums[i + len] - dp[i][i + len - 1], nums[i] - dp[i + 1][i + len]);
            }
        }
        return dp[0][n - 1] >= 0;
    }
};