/*
1595. Minimum Cost to Connect Two Groups of Points
https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/

You are given two groups of points where the first group has size1 points,
the second group has size2 points, and size1 >= size2.

The cost of the connection between any two points are given in an size1 x size2 matrix
where cost[i][j] is the cost of connecting point i of the first group and point j of the second group.
The groups are connected if each point in both groups is connected to one or more points in the opposite group.
In other words, each point in the first group must be connected to at least one point in the second group,
and each point in the second group must be connected to at least one point in the first group.

Return the minimum cost it takes to connect the two groups.

Example 1:
Input: cost = [[15, 96], [36, 2]]
Output: 17
Explanation: The optimal way of connecting the groups is:
1--A
2--B
This results in a total cost of 17.

Example 2:
Input: cost = [[1, 3, 5], [4, 1, 1], [1, 5, 3]]
Output: 4
Explanation: The optimal way of connecting the groups is:
1--A
2--B
2--C
3--A
This results in a total cost of 4.
Note that there are multiple points connected to point 2 in the first group and point A in the second group. This does not matter as there is no limit to the number of points that can be connected. We only care about the minimum total cost.

Example 3:
Input: cost = [[2, 5, 1], [3, 4, 7], [8, 1, 2], [6, 2, 4], [3, 8, 8]]
Output: 10

Constraints:
size1 == cost.length
size2 == cost[i].length
1 <= size1, size2 <= 12
size1 >= size2
0 <= cost[i][j] <= 100
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
#include <cfloat>
#include <stdio.h>
#include <map>
using namespace std;
/*
Explanation: dp[i][mask] = represents the state of the first i of group 1 being connected, with mask representing which nodes of group 2 have been covered already by previous steps in the DFS (mask[k] = 1 if node k in group 2 has been connected)
So we must calculate how to cover the rest [i+1, n) of group 1
At the end, there is a clever optimization: we look at what hasn't been covered in group 2 and connect it to group 1 using its cheapest edge

Please correct me if l understood any of this wrong @votrubac

Edit: even after reading this solution, I couldn't understand how anyone could have arrived at this. But alas, I have an explanation.

The most brute force way would be to try all options for all nodes = O(N^M*M^N).
But once we have all the Group 1 matches, it's easy to see each Group 2 node can be matched greedily using its precalculated minimum edge = O(N^M*M).
We can optimize this by only connecting the nodes in Group 2 that weren't already connected by anything in Group 1. There are 2^M possible states for which Group 2 nodes have been connected, and we are likely to encounter each many times from all possible connections of Group 1, so we can calculate/memorize this result for the end (when all of Group 1 has been connected) = O(N^M*2^M).
However, we can memoize this at each step in connecting Group 1, which brings us to N2^M possible states, each taking M time to calculate = O(NM*2^M)
*/
class Solution {
public:
    int dp[13][4096] = {};
    int dfs(vector<vector<int>>& cost, vector<int> &min_sz2, int i, int mask) {
        if (dp[i][mask])
            return dp[i][mask] - 1;
        int res = i >= cost.size() ? 0 : INT_MAX;
        if (i >= cost.size())
            for (auto j = 0; j < cost[0].size(); ++j)
                res += min_sz2[j] * ((mask & (1 << j)) == 0);
        else
            for (auto j = 0; j < cost[0].size(); ++j)
                res = min(res, cost[i][j] + dfs(cost, min_sz2, i + 1, mask | (1 << j)));
        dp[i][mask] = res + 1;
        return res;
    }
    int connectTwoGroups(vector<vector<int>>& cost) {
        vector<int> min_sz2(cost[0].size(), INT_MAX);
        for (int j = 0; j < min_sz2.size(); ++j)
            for (int i = 0; i < cost.size(); ++i)
                min_sz2[j] = min(min_sz2[j], cost[i][j]);
        return dfs(cost, min_sz2, 0, 0);
    }
};
