/*
1391. Check if There is a Valid Path in a Grid
https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/

Given a m x n grid. Each cell of the grid represents a street. The street of grid[i][j] can be:
1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.


You will initially start at the street of the upper-left cell (0,0).
A valid path in the grid is a path which starts from the upper left cell (0,0)
and ends at the bottom-right cell (m - 1, n - 1).
The path should only follow the streets.

Notice that you are not allowed to change any street.
Return true if there is a valid path in the grid or false otherwise.

Example 1:
Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).

Example 2:
Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)

Example 3:
Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).

Example 4:
Input: grid = [[1,1,1,1,1,1,3]]
Output: true

Example 5:
Input: grid = [[2],[2],[2],[2],[2],[2],[6]]
Output: true

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<int> > &grid) {
        vector<vector<vector<int> > > directs({
            {{0, -1}, {0, 1}},
            {{-1, 0}, {1, 0}},
            {{0, -1}, {1, 0}},
            {{0, 1}, {1, 0}},
            {{0, -1}, {-1, 0}},
            {{0, 1}, {-1, 0}}
        });

        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        queue<vector<int> > bfs;
        bfs.push({0, 0});
        visited[0][0] = true;
        while (!bfs.empty()) {
            vector<int> cur = bfs.front();
            bfs.pop();

            int row = cur[0];
            int col = cur[1];
            int type = grid[row][col] - 1;
            for (auto &dir: directs[type]) {
                int nr = row + dir[0];
                int nc = col + dir[1];
                if (nr < 0 or nr
                >=
                m or nc<0 or nc >= n or visited[nr][nc]
                )
                {
                    continue;
                }

                for (auto &backDir: directs[grid[nr][nc] - 1])
                    if (nr + backDir[0] == row and nc
                +backDir[1] == col
                )
                {
                    visited[nr][nc] = true;
                    bfs.push({nr, nc});
                }
            }
        }
        return visited[m - 1][n - 1];
    }
};