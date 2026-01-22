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
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than
route [1,3,5,3,5].

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
#include <climits>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();

        vector<vector<int>> efforts(m, vector<int>(n, INT_MAX));
        efforts[0][0] = 0;

        int dirs[5] = {-1, 0, 1, 0, -1};
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});  // {pos, effort}

        while (!pq.empty()) {
            int row = pq.top().first / n;
            int col = pq.top().first % n;
            int effort = pq.top().second;
            pq.pop();

            if (effort > efforts[row][col]) {
                continue;
            }

            if (row == m - 1 && col == n - 1) {
                return effort;
            }

            for (int i = 0; i < 4; ++i) {
                int next_row = row + dirs[i];
                int next_col = col + dirs[i + 1];
                if (next_row >= m || next_col >= n || next_row < 0 || next_col < 0) {
                    continue;
                }

                int next_effort = max(effort, abs(heights[row][col] - heights[next_row][next_col]));
                if (next_effort < efforts[next_row][next_col]) {
                    efforts[next_row][next_col] = next_effort;
                    pq.push({next_row * n + next_col, next_effort});
                }
            }
        }
        return -1;
    }
};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[0][0] = 0;

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>
                pq;
        pq.push({0, {0, 0}});

        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};
        while (!pq.empty()) {
            int diff = pq.top().first;
            int r = pq.top().second.first;
            int c = pq.top().second.second;
            pq.pop();

            if (r == n - 1 && c == m - 1) {
                return diff;
            }

            for (int i = 0; i < 4; i++) {
                int nrow = r + dr[i];
                int ncol = c + dc[i];

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m) {
                    int newEffort = max(abs(heights[r][c] - heights[nrow][ncol]), diff);
                    if (newEffort < dist[nrow][ncol]) {
                        dist[nrow][ncol] = newEffort;
                        pq.push({newEffort, {nrow, ncol}});
                    }
                }
            }
        }

        return 0;
    }
};
