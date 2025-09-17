/*
1155. Number of Dice Rolls With Target Sum
You have d dice, and each die has f faces numbered 1, 2, ..., f.

Return the number of possible ways (out of fd total ways) modulo 10^9 + 7 to roll the dice
so the sum of the face up numbers equals target.

Example 1:

Input: d = 1, f = 6, target = 3
Output: 1
Explanation:
You throw one die with 6 faces.  There is only one way to get a sum of 3.
Example 2:

Input: d = 2, f = 6, target = 7
Output: 6
Explanation:
You throw two dice, each with 6 faces.  There are 6 ways to get a sum of 7:
1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
Example 3:

Input: d = 2, f = 5, target = 10
Output: 1
Explanation:
You throw two dice, each with 5 faces.  There is only one way to get a sum of 10: 5+5.
Example 4:

Input: d = 1, f = 2, target = 3
Output: 0
Explanation:
You throw one die with 2 faces.  There is no way to get a sum of 3.
Example 5:

Input: d = 30, f = 30, target = 500
Output: 222616187
Explanation:
The answer must be returned modulo 10^9 + 7.


Constraints:

1 <= d, f <= 30
1 <= target <= 1000
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
using namespace std;

class Solution { // 33.7%
private:
    int mod = 1e9 + 7;
public:
    int numRollsToTarget(int d, int f, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= d; ++i) {
            vector<int> dp1(target + 1);
            for (int j = 1; j <= f; ++j) {
                for (auto k = j; k <= target; ++k) {
                    dp1[k] = (dp1[k] + dp[k - j]) % mod;
                }
            }
            swap(dp, dp1);
        }
        return dp[target];
    }
};

class Solution1 { // 33.7% 2D DP
private:
    int mod = 1e9 + 7;
public:
    int numRollsToTarget(int d, int f, int target) {
        vector<vector<int>> dp(d + 1, vector<int>(target + 1, 0));
        for (int i = 1; i <= min(f, target); ++i) {
            dp[1][i] = 1;
        }
        for (int i = 2; i <= d; ++i) {
            for (int j = 1; j <= target; ++j) {
                for (int k = 1; k <= f; ++k) if (j - k >= 1) {
                    dp[i][j] += dp[i - 1][j - k];
                    dp[i][j] %= mod;
                }
            }
        }
        return dp[d][target];
    }
};
