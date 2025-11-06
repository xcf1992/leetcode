/*
1293. Shortest Path in a Grid with Obstacles Elimination
https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle).
In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1)
given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

Example 1:
Input:
grid =
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]],
k = 1
Output: 6
Explanation:
The shortest path without eliminating any obstacle is 10.
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) ->
(2,2) -> (3,2) -> (4,2).

Example 2:
Input:
grid =
[[0,1,1],
 [1,1,1],
 [1,0,0]],
k = 1
Output: -1
Explanation:
We need to eliminate at least two obstacles to find such a walk.

Constraints:
grid.length == m
grid[0].length == n
1 <= m, n <= 40
1 <= k <= m*n
grid[i][j] == 0 or 1
grid[0][0] == grid[m-1][n-1] == 0
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
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
m*n*k may be too redundant,
we will repeatly go back and visit some visited nodes with higher eliminate number
*/
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        queue<vector<int>> bfs;
        bfs.push({0, 0, 0});
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k + 1, false)));
        visited[0][0][0] = true;

        vector<int> diff({0, 1, 0, -1, 0});
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int row = bfs.front()[0];
                int col = bfs.front()[1];
                int curK = bfs.front()[2];
                bfs.pop();

                if (row == m - 1 and col == n - 1) {
                    return result;
                }

                for (int j = 1; j < diff.size(); ++j) {
                    int nexR = row + diff[j];
                    int nexC = col + diff[j - 1];
                    int nexK = curK;
                    if (nexR >= 0 and nexC >= 0 and nexR < m and nexC < n) {
                        if (grid[nexR][nexC] == 1) {
                            nexK += 1;
                        }
                        if (nexK <= k and !visited[nexR][nexC][nexK]) {
                            visited[nexR][nexC][nexK] = true;
                            bfs.push({nexR, nexC, nexK});
                        }
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};
