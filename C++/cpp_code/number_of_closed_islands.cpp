/*
1254. Number of Closed Islands
https://leetcode.com/problems/number-of-closed-islands/

Given a 2D grid consists of 0s (land) and 1s (water).
An island is a maximal 4-directionally connected group of 0s
and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

Example 1:
Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation:
Islands in gray are closed because they are completely surrounded by water (group of 1s).

Example 2:
Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1

Example 3:
Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2

Constraints:
1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1
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
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    void dfs(int row, int col, vector<vector<int>>& grid) {
        if (row < 0 or col < 0 or row >= m or col >= n or grid[row][col] == 1) {
            return;
        }

        grid[row][col] = 1;
        for (int i = 1; i < diff.size(); ++i) {
            dfs(row + diff[i], col + diff[i - 1], grid);
        }
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        if (m == 0) {
            return 0;
        }
        n = grid[0].size();

        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) {
                dfs(i, 0, grid);
            }
            if (grid[i][n - 1] == 0) {
                dfs(i, n - 1, grid);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 0) {
                dfs(0, j, grid);
            }
            if (grid[m - 1][j] == 0) {
                dfs(m - 1, j, grid);
            }
        }

        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    result += 1;
                    dfs(i, j, grid);
                }
            }
        }
        return result;
    }
};