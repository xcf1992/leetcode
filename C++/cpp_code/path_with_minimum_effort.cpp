/*
1631. Path With Minimum Effort
https://leetcode.com/problems/path-with-minimum-effort/

You are a hiker preparing for an upcoming hike.
You are given heights, a 2D array of size rows x columns,
where heights[row][col] represents the height of cell (row, col).
You are situated in the top-left cell, (0, 0),
and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed).
You can move up, down, left, or right,
and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example 1:
Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.

Constraints:
rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 106
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
#include <set>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int> > &heights) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push({0, 0});

        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int> > efforts(m, vector<int>(n, INT_MAX));

        int dirs[5] = {-1, 0, 1, 0, -1};
        while (!pq.empty()) {
            int row = pq.top().first / n;
            int col = pq.top().first % n;
            int effort = pq.top().second;
            pq.pop();

            if (row == m - 1 and col
            ==
            n - 1
            )
            {
                return effort;
            }

            if (effort >= efforts[row][col]) {
                continue;
            }

            efforts[row][col] = effort;
            for (int i = 0; i < 4; ++i) {
                int nr = row + dirs[i];
                int nc = col + dirs[i + 1];
                if (nr >= m or nc
                >=
                n or nr<0 or nc < 0
                )
                {
                    continue;
                }
                int nEffort = max(effort, abs(heights[row][col] - heights[nr][nc]));
                pq.push({nr * n + nc, nEffort});
            }
        }
        return -1;
    }
};