/*
1034. Coloring A Border
https://leetcode.com/problems/coloring-a-border/

Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.

Two squares belong to the same connected component
if and only if they have the same color and are next to each other in any of the 4 directions.

The border of a connected component is all the squares in the connected component
that are either 4-directionally adjacent to a square not in the component,
or on the boundary of the grid (the first or last row or column).

Given a square at location (r0, c0) in the grid and a color,
color the border of the connected component of that square with the given color,
and return the final grid.

Example 1:

Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
Output: [[3, 3], [3, 2]]
Example 2:

Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
Output: [[1, 3, 3], [2, 3, 3]]
Example 3:

Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]


Note:

1 <= grid.length <= 50
1 <= grid[0].length <= 50
1 <= grid[i][j] <= 1000
0 <= r0 < grid.length
0 <= c0 < grid[0].length
1 <= color <= 1000
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
#include <climits>
#include <map>
#include <set>
using namespace std;

class Solution {
private:
    bool isBorder(int r, int c, int m, int n, vector<vector<int>>& grid) {
        if (r == 0 or r == m - 1 or c == 0 or c == n - 1) {
            return true;
        }

        int color = grid[r][c];
        if (color == grid[r - 1][c] and color == grid[r + 1][c] and color == grid[r][c - 1] and
            color == grid[r][c + 1]) {
            return false;
        }
        return true;
    }

public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> border;
        queue<pair<int, int>> bfs;
        bfs.push({r0, c0});
        visited[r0][c0] = true;

        vector<int> rDiff = {0, 0, 1, -1};
        vector<int> cDiff = {1, -1, 0, 0};
        while (!bfs.empty()) {
            int row = bfs.front().first;
            int col = bfs.front().second;
            bfs.pop();

            if (isBorder(row, col, m, n, grid)) {
                border.push_back({row, col});
            }

            for (int i = 0; i < 4; ++i) {
                int nRow = row + rDiff[i];
                int nCol = col + cDiff[i];
                if (nRow >= 0 and nRow < m and nCol >= 0 and nCol < n and !visited[nRow][nCol] and
                    grid[nRow][nCol] == grid[r0][c0]) {
                    visited[nRow][nCol] = true;
                    bfs.push({nRow, nCol});
                }
            }
        }

        for (pair<int, int>& b : border) {
            grid[b.first][b.second] = color;
        }
        return grid;
    }
};