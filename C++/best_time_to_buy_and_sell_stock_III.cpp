/*
123. Best Time to Buy and Sell Stock III
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> left(n, 0);
        int maxProfit = 0;
        int curMin = prices[0];
        for (int i = 0; i < n; ++i) {
            curMin = min(prices[i], curMin);
            maxProfit = max(maxProfit, prices[i] - curMin);
            left[i] = maxProfit;
        }

        vector<int> right(n, 0);
        maxProfit = 0;
        int curMax = prices[n - 1];
        for (int j = n - 1; j >= 0; --j) {
            curMax = max(prices[j], curMax);
            maxProfit = max(maxProfit, curMax - prices[j]);
            right[j] = maxProfit;
        }

        int result = 0;
        for (int i = 0; i < n - 1; ++i) {
            result = max(result, left[i] + right[i + 1]);
        }
        // compare between if we only make 1 transaction
        return max(result, max(right[0], left[n - 1]));
    }
};

/*
Input
[1,2,4,2,5,7,2,4,9,0]
Output
12
Expected
13
*/
class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        int p1 = 0;
        int p2 = 0;
        int curMin = prices[0];
        int curMax = prices[0];
        for (int i = 1; i < n; i++) {
            if (prices[i] < curMax) {
                int profit = curMax - curMin;
                if (profit > p2) {
                    p1 = p2;
                    p2 = profit;
                }
                else if (profit > p1) {
                    p1 = profit;
                }
                curMin = prices[i];
            }
            curMax = prices[i];
        }
        if (curMax > curMin) {
            int profit = curMax - curMin;
            if (profit > p2) {
                p1 = p2;
                p2 = profit;
            }
            else if (profit > p1) {
                p1 = profit;
            }
        }
        return p1 + p2;
    }
};
