/*
121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock),
design an algorithm to find the curMaximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. curMax profit = 0.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int result = 0;
        int curMin = INT_MAX;
        for (int price: prices) {
            curMin = min(curMin, price);
            result = max(result, price - curMin);
        }
        return result;
    }
};

class Solution1 {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }

        int profit = 0;
        int curMin = prices[0];
        int curMax = prices[0];
        for (int i = 1; i < n; i++) {
            if (prices[i] > curMax) {
                curMax = prices[i];
            } else if (prices[i] < curMin) {
                profit = max(profit, curMax - curMin);
                curMax = curMin = prices[i];
            }
        }
        return max(profit, curMax - curMin);
    }
};