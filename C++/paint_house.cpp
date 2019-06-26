/*
256. Paint House
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Example:

Input: [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
             Minimum cost: 2 + 5 + 3 = 10.
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

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) {
            return 0;
        }

        vector<int> dp(costs[0]);
        for (int i = 1; i < costs.size(); i++) {
            int newR = min(dp[1], dp[2]) + costs[i][0];
            int newB = min(dp[0], dp[2]) + costs[i][1];
            int newY = min(dp[0], dp[1]) + costs[i][2];
            dp[0] = newR;
            dp[1] = newB;
            dp[2] = newY;
        }

        int result = dp[0];
        for (int cost : dp) {
            result = min(result, cost);
        }
        return result;
    }
};
