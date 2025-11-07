/*
https://leetcode.com/problems/shortest-path-to-get-food
1730. Shortest Path to Get Food

You are starving and you want to eat food as quickly as possible. You want to find the shortest path to arrive at any
food cell.

You are given an m x n character matrix, grid, of these different types of cells:

'*' is your location. There is exactly one '*' cell.
'#' is a food cell. There may be multiple food cells.
'O' is free space, and you can travel through these cells.
'X' is an obstacle, and you cannot travel through these cells.
You can travel to any adjacent cell north, east, south, or west of your current location if there is not an obstacle.

Return the length of the shortest path for you to reach any food cell. If there is no path for you to reach food, return
-1.



Example 1:


Input: grid = [["X","X","X","X","X","X"],["X","*","O","O","O","X"],["X","O","O","#","O","X"],["X","X","X","X","X","X"]]
Output: 3
Explanation: It takes 3 steps to reach the food.
Example 2:


Input: grid = [["X","X","X","X","X"],["X","*","X","O","X"],["X","O","X","#","X"],["X","X","X","X","X"]]
Output: -1
Explanation: It is not possible to reach the food.
Example 3:


Input: grid =
[["X","X","X","X","X","X","X","X"],["X","*","O","X","O","#","O","X"],["X","O","O","X","O","O","X","X"],["X","O","O","O","O","#","O","X"],["X","X","X","X","X","X","X","X"]]
Output: 6
Explanation: There can be multiple food cells. It only takes 6 steps to reach the bottom food.
Example 4:

Input: grid =
[["X","X","X","X","X","X","X","X"],["X","*","O","X","O","#","O","X"],["X","O","O","X","O","O","X","X"],["X","O","O","O","O","#","O","X"],["O","O","O","O","O","O","O","O"]]
Output: 5


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[row][col] is '*', 'X', 'O', or '#'.
The grid contains exactly one '*'.
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
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '#') {
                    visited[i][j] = true;
                    bfs.push({i, j});
                }
            }
        }

        int rst = 1;
        vector<int> diff({0, 1, 0, -1, 0});
        while (!bfs.empty()) {
            int cnt = bfs.size();
            for (int i = 0; i < cnt; i++) {
                int row = bfs.front().first;
                int col = bfs.front().second;
                bfs.pop();

                for (int j = 0; j < 4; j++) {
                    int nxt_row = row + diff[j];
                    int nxt_col = col + diff[j + 1];

                    if (nxt_row < 0 || nxt_row >= m || nxt_col < 0 || nxt_col >= n) {
                        continue;
                    }

                    if (grid[nxt_row][nxt_col] == 'X' || visited[nxt_row][nxt_col]) {
                        continue;
                    }

                    if (grid[nxt_row][nxt_col] == '0') {
                        return rst;
                    }

                    visited[nxt_row][nxt_col] = true;
                    bfs.push({nxt_row, nxt_col});
                }
            }
            rst += 1;
        }
        return -1;
    }
};
