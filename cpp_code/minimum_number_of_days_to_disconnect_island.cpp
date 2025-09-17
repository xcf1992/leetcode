/*
1568. Minimum Number of Days to Disconnect Island
https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/

Given a 2D grid consisting of 1s (land) and 0s (water).
An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
In one day, we are allowed to change any single land cell (1) into a water cell (0).
Return the minimum number of days to disconnect the grid.

Example 1:
Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
Output: 2
Explanation: We need at least 2 days to get a disconnected grid.
Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.

Example 2:
Input: grid = [[1,1]]
Output: 2
Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.

Example 3:
Input: grid = [[1,0,1,0]]
Output: 0

Example 4:
Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,0,1,1]]
Output: 1

Example 5:
Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,1,1,1]]
Output: 2

Constraints:
1 <= grid.length, grid[i].length <= 30
grid[i][j] is 0 or 1.
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
Observation
ans <= 2
ans is always less-equal to 2

why?
for any island we can remove the two blocks around the bottom left corner to make it disconnected

x x x
x . x
x x x
can be changed to

x x x
x . .
x . x
if you still don't get it read this: comment
we need to check for only when ans is 1 or 0

ans = 1
we remove a block and check if it disconnects the islands

ans = 0
we check if there are > 1 islands already
*/
class Solution {
private:
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    int m = 0;
    int n = 0;

    void dfs(int x, int y, vector<vector<int>>& grid, vector<vector<int>>& vis) {
        if (x < 0 or y < 0 or x >= n or y >= m or vis[x][y] or grid[x][y] == 0) {
            return;
        }

        vis[x][y] = 1;
        for (int a = 0; a < 4; a++) {
            dfs(x + dx[a], y + dy[a], grid, vis);
        }
    }

    int count_islands(vector<vector<int>> & grid) {
        int count = 0;
        vector<vector<int>> vis(n, vector<int> (m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] and grid[i][j]) {
                    count++;
                    dfs(i, j, grid, vis);
                }
            }
        }
        return count;
    }
public:
    int minDays(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
		// check for 0 ans
        int islands = count_islands(grid);
        if (islands > 1 or islands == 0) {
            return 0;
        }

        for (int i = 0 ; i < n; i ++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]) {
                    grid[i][j] = 0;
                    islands = count_islands(grid);
                    if (islands > 1 or islands == 0) {
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
};
