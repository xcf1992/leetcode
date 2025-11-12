/*
https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/description/
2617. Minimum Number of Visited Cells in a Grid

You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).

Starting from the cell (i, j), you can move to one of the following cells:

Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid
path, return -1.



Example 1:


Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
Output: 4
Explanation: The image above shows one of the paths that visits exactly 4 cells.
Example 2:


Input: grid = [[3,4,2,1],[4,2,1,1],[2,1,1,0],[3,4,1,0]]
Output: 3
Explanation: The image above shows one of the paths that visits exactly 3 cells.
Example 3:


Input: grid = [[2,1,0],[1,0,0]]
Output: -1
Explanation: It can be proven that no path exists.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 105
1 <= m * n <= 105
0 <= grid[i][j] < m * n
grid[m - 1][n - 1] == 0
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
using namespace std;

class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<set<int>> visited_col(m);
        vector<set<int>> visited_row(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                visited_col[i].insert(j);
                visited_row[j].insert(i);
            }
        }

        queue<vector<int>> bfs;  // row, col, distance
        bfs.push({0, 0, 1});
        while (!bfs.empty()) {
            int row = bfs.front()[0];
            int col = bfs.front()[1];
            int dis = bfs.front()[2];
            bfs.pop();
            if (row == m - 1 && col == n - 1) {
                return dis;
            }

            auto it = visited_col[row].lower_bound(col + 1);
            while (it != visited_col[row].end() && *it <= col + grid[row][col]) {
                bfs.push({row, *it, dis + 1});
                visited_row[*it].erase(row);
                visited_col[row].erase(it++);
            }

            it = visited_row[col].lower_bound(row + 1);
            while (it != visited_row[col].end() && *it <= row + grid[row][col]) {
                bfs.push({*it, col, dis + 1});
                visited_col[*it].erase(col);
                visited_row[col].erase(it++);
            }
        }
        return -1;
    }
};
