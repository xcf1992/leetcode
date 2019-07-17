/*
714. Best Time to Buy and Sell Stock with Transaction Fee
Your are given an array of integers prices,
for which the i-th element is the price of a given stock on day i;
and a non-negative integer fee representing a transaction fee.

You may complete as many transactions as you like,
but you need to pay the transaction fee for each transaction.
You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Note:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.
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

/*
Definition:
hold[i] - the maximum profit you can earn if you have to hold at day[i]
sold[i] - the maximum profit you can earn if you have to sold at day[i]

Formula:
hold[i] = max(hold[i - 1], sold[i - 1] - p[i])       // if hold at [i-1], no op; if sold at [i-1], buy at [i] with cost of p[i];
sold[i] = max(sold[i - 1], hold[i - 1] + p[i] - fee) // if sold at [i-1], no op; if hold at [i-1], sell at [i] with gain of p[i] - fee;

Initialization:
hold[0] = 0 - price[0];  // buy shares with cost of p[0];
sold[0] = 0;             // no op no cost;
*/
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int haveStockProfit = INT_MIN;
        int noStockProfit = 0;
        for (int price : prices) {
            int temp = noStockProfit;
            noStockProfit = max(noStockProfit, haveStockProfit + price);
            haveStockProfit = max(haveStockProfit, temp - price - fee);
        }
        return noStockProfit;
    }
};
