/*
https://leetcode.com/problems/maximum-profit-from-trading-stocks/description/
2291. Maximum Profit From Trading Stocks

You are given two 0-indexed integer arrays of the same length present and future where present[i] is the current price
of the ith stock and future[i] is the price of the ith stock a year in the future. You may buy each stock at most once.
You are also given an integer budget representing the amount of money you currently have.

Return the maximum amount of profit you can make.



Example 1:

Input: present = [5,4,6,2,3], future = [8,5,4,3,5], budget = 10
Output: 6
Explanation: One possible way to maximize your profit is to:
Buy the 0th, 3rd, and 4th stocks for a total of 5 + 2 + 3 = 10.
Next year, sell all three stocks for a total of 8 + 3 + 5 = 16.
The profit you made is 16 - 10 = 6.
It can be shown that the maximum profit you can make is 6.
Example 2:

Input: present = [2,2,5], future = [3,4,10], budget = 6
Output: 5
Explanation: The only possible way to maximize your profit is to:
Buy the 2nd stock, and make a profit of 10 - 5 = 5.
It can be shown that the maximum profit you can make is 5.
Example 3:

Input: present = [3,3,12], future = [0,3,15], budget = 10
Output: 0
Explanation: One possible way to maximize your profit is to:
Buy the 1st stock, and make a profit of 3 - 3 = 0.
It can be shown that the maximum profit you can make is 0.


Constraints:

n == present.length == future.length
1 <= n <= 1000
0 <= present[i], future[i] <= 100
0 <= budget <= 1000
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
#include <set>
using namespace std;

class Solution {
public:
    int maximumProfit(vector<int>& present, vector<int>& future, int budget) {
        int n = present.size();
        vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= budget; j++) {
                dp[i][j] = dp[i - 1][j];
                if (future[i - 1] > present[i - 1] && j >= present[i - 1]) {
                    dp[i][j] = max(dp[i][j], future[i - 1] - present[i - 1] + dp[i - 1][j - present[i - 1]]);
                }
            }
        }
        return dp[n][budget];
    }
};
