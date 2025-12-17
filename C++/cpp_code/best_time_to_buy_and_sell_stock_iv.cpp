/*
188. Best Time to Buy and Sell Stock IV
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Example 1:

Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
             Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
 * dp[i, j] represents the max profit up until prices[j] using at most i transactions.
 * dp[i, j] = max(dp[i, j-1], max(prices[j] - prices[jj] + dp[i-1, jj])) { jj in range of [0, j-1] }
 *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj]))
 * dp[0, j] = 0; 0 transactions makes 0 profit
 * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.

Explanation:
For example, if j == 8, then amongst all jj == 1,2,...,7
The max profit could be one of the following:
dp[i-1][0] + prices[8] - prices[0]
dp[i-1][1] + prices[8] - prices[1]
dp[i-1][2] + prices[8] - prices[2]
...
dp[i-1][6] + prices[8] - prices[6]
dp[i-1][7] + prices[8] - prices[7]

localMax is the max value amongst all:
dp[i-1][0] - prices[0]
dp[i-1][1] - prices[1]
dp[i-1][2] - prices[2]
...
dp[i-1][6] - prices[6]
dp[i-1][7] - prices[7]

Then localMax + prices[8] is the max profit if we sell the stock at day 8.
Then we compare this result with the max profit of not selling the stock at day 8, take the max of the two.
*/
class Solution {
private:
    int get_max_profit(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                result += prices[i] - prices[i - 1];
            }
        }
        return result;
    }

public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }

        if (k > n / 2) {
            return get_max_profit(prices);
        }

        vector<vector<int>> dp(k + 1, vector<int>(n, 0));
        for (int count = 1; count <= k; ++count) {
            int curMax = dp[count - 1][0] - prices[0];
            for (int i = 1; i < n; ++i) {
                dp[count][i] = max(dp[count][i - 1], prices[i] + curMax);
                curMax = max(curMax, dp[count - 1][i] - prices[i]);
            }
        }
        return dp[k][n - 1];
    }
};