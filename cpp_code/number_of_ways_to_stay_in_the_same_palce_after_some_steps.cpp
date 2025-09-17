/*
1269. Number of Ways to Stay in the Same Place After Some Steps
https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/

You have a pointer at index 0 in an array of size arrLen.
At each step, you can move 1 position to the left,
1 position to the right in the array or stay in the same place
(The pointer should not be placed outside the array at any time).

Given two integers steps and arrLen,
return the number of ways such that your pointer still at index 0 after exactly steps steps.

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay

Example 2:
Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay

Example 3:
Input: steps = 4, arrLen = 2
Output: 8

Constraints:
1 <= steps <= 500
1 <= arrLen <= 10^6
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

class Solution {
public:
    int numWays(int steps, int arrLen) {
        int mod = 1e9 + 7;
        int len = min(steps / 2 + 1, arrLen);
        vector<int> dp(len + 2, 0);
        dp[1] = 1;
        for (int i = 0; i < steps; ++i) {
            vector<int> temp(len + 2, 0);
            for (int k = 1; k <= len; ++k) {
                temp[k] = ((long)dp[k - 1] + (long)dp[k] + (long)dp[k + 1]) % mod;
            }
            dp = temp;
        }
        return dp[1];
    }
};
