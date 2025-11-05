/*
1473. Paint House III
https://leetcode.com/problems/paint-house-iii/

There is a row of m houses in a small city,
each house must be painted with one of the n colors (labeled from 1 to n),
some houses that has been painted last summer should not be painted again.

A neighborhood is a maximal group of continuous houses that are painted with the same color.
(For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods  [{1}, {2,2}, {3,3}, {2}, {1,1}]).

Given an array houses, an m * n matrix cost and an integer target where:

houses[i]: is the color of the house i, 0 if the house is not painted yet.
cost[i][j]: is the cost of paint the house i with the color j+1.
Return the minimum cost of painting all the remaining houses
in such a way that there are exactly target neighborhoods,
if not possible return -1.

Example 1:
Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 9
Explanation: Paint houses of this way [1,2,2,1,1]
This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.

Example 2:
Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 11
Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
Cost of paint the first and last house (10 + 1) = 11.

Example 3:
Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
Output: 5

Example 4:
Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
Output: -1
Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.

Constraints:
m == houses.length == cost.length
n == cost[i].length
1 <= m <= 100
1 <= n <= 20
1 <= target <= m
0 <= houses[i] <= n
1 <= cost[i][j] <= 10^4
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
#include <set>
using namespace std;

class Solution {
public:
    int dp[101][101][21] = {};

    int dfs(vector<int> &houses, vector<vector<int> > &cost, int i, int target, int last_clr) {
        if (i >= houses.size() || target < 0)
            return target == 0 ? target : 1000001;
        if (houses[i] != 0) // painted last year.
            return dfs(houses, cost, i + 1, target - (last_clr != houses[i]), houses[i]);
        if (dp[i][target][last_clr])
            return dp[i][target][last_clr];
        auto res = 1000001;
        for (auto clr = 1; clr <= cost[i].size(); ++clr) {
            res = min(res, cost[i][clr - 1]
                           + dfs(houses, cost, i + 1, target - (last_clr != clr), clr));
        }
        return dp[i][target][last_clr] = res;
    }

    int minCost(vector<int> &houses, vector<vector<int> > &cost, int m, int n, int target) {
        auto res = dfs(houses, cost, 0, target, 0);
        return res > 1000000 ? -1 : res;
    }
};