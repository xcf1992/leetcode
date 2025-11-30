/*
1230. Toss Strange Coins
https://leetcode.com/problems/toss-strange-coins/

You have some coins.
The i-th coin has a probability prob[i] of facing heads when tossed.
Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.

Example 1:
Input: prob = [0.4], target = 1
Output: 0.40000

Example 2:
Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
Output: 0.03125

Constraints:
1 <= prob.length <= 1000
0 <= prob[i] <= 1
0 <= target <= prob.length
Answers will be accepted as correct if they are within 10^-5 of the correct answer.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        if (target > n) {
            return 0.0;
        }

        vector<vector<double>> dp(n + 1, vector<double>(target + 1, 0.0));
        dp[0][0] = 1.0;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = (1.0 - prob[i - 1]) * dp[i - 1][0];
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j)
                if (j <= i) {
                    dp[i][j] = dp[i - 1][j - 1] * prob[i - 1] + dp[i - 1][j] * (1.0 - prob[i - 1]);
                }
        }
        return dp[n][target];
    }
};