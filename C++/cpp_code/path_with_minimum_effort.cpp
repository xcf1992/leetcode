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
        int left = 0;
        int right = INT_MAX;
        int result = INT_MAX;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can_reach(heights, mid)) {
                result = min(result, mid);
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return result;
    }

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // use bfs to check if we can reach destination with max absolute difference
    // k
    bool can_reach(vector<vector<int>>& heights, int mid) {
        int row = heights.size();
        int col = heights[0].size();
        queue<Cell> queue;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        queue.push(Cell(0, 0));
        visited[0][0] = true;
        while (!queue.empty()) {
            Cell curr = queue.front();
            queue.pop();
            if (curr.x == row - 1 && curr.y == col - 1) {
                return true;
            }
            for (auto direction : directions) {
                int adjacentX = curr.x + direction[0];
                int adjacentY = curr.y + direction[1];
                if (isValidCell(adjacentX, adjacentY, row, col) && !visited[adjacentX][adjacentY]) {
                    int currentDifference = abs(heights[adjacentX][adjacentY] - heights[curr.x][curr.y]);
                    if (currentDifference <= mid) {
                        visited[adjacentX][adjacentY] = true;
                        queue.push(Cell(adjacentX, adjacentY));
                    }
                }
            }
        }
        return false;
    }

    bool isValidCell(int x, int y, int row, int col) {
        return x >= 0 && x <= row - 1 && y >= 0 && y <= col - 1;
    }

    class Cell {
    public:
        int x, y;
        Cell(int x, int y) {
            this->x = x;
            this->y = y;
        }
    };
};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<int> diff({0, 1, 0, -1, 0});

        vector<vector<int>> efforts(m, vector<int>(n, INT_MAX));
        efforts[0][0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            int cur_effort = pq.top().first;
            int cur_r = pq.top().second / n;
            int cur_c = pq.top().second % n;
            pq.pop();

            if (cur_effort > efforts[cur_r][cur_c]) {
                continue;
            }

            if (cur_r == m - 1 && cur_c == n - 1) {
                return cur_effort;
            }

            for (int i = 0; i < 4; i++) {
                int next_r = cur_r + diff[i];
                int next_c = cur_c + diff[i + 1];
                if (next_r < 0 || next_r >= m || next_c < 0 || next_c >= n) {
                    continue;
                }

                int next_effort = abs(heights[cur_r][cur_c] - heights[next_r][next_c]);
                int max_effort = max(cur_effort, next_effort);
                if (max_effort < efforts[next_r][next_c]) {
                    efforts[next_r][next_c] = max_effort;
                    pq.push({max_effort, next_r * n + next_c});
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
