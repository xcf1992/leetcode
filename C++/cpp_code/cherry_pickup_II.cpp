/*
1463. Cherry Pickup II
https://leetcode.com/problems/cherry-pickup-ii/

Given a rows x cols matrix grid representing a field of cherries.
Each cell in grid represents the number of cherries that you can collect.

You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) ,
and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

Return the maximum number of cherries collection using both robots  by following the rules below:

From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
When both robots stay on the same cell, only one of them takes the cherries.
Both robots cannot move outside of the grid at any moment.
Both robots should reach the bottom row in the grid.

Example 1:
Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.

Example 2:
Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.

Example 3:
Input: grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
Output: 22

Example 4:
Input: grid = [[1,1],[1,1]]
Output: 4

Constraints:
rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100
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
#include <set>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
Idea
This is dp solution.
At each step, we move both robot1 and robot2 to next row,
and with all possibles columns (j-1, j, j+1).
Please keep in mind that if 2 robots go the same cell, we only collect cherries once.

Complexity
Time: O(9 * m * n^2), where m is number of rows, n is number of cols of grid.
Space: O(m * n^2)
*/
class Solution {
private:
    int dp[70][70][70] = {};
    int m = 0;
    int n = 0;

    int dfs(vector<vector<int>>& grid, int r, int c1, int c2) {
        if (r == m) {
            return 0; // Reach to bottom row
        }

        if (dp[r][c1][c2] != -1) {
            return dp[r][c1][c2];
        }

        dp[r][c1][c2] = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nc1 = c1 + i;
                int nc2 = c2 + j;
                if (nc1 >= 0 and nc1 < n and nc2 >= 0 and nc2 < n) {
                    dp[r][c1][c2] = max(dp[r][c1][c2], dfs(grid, r + 1, nc1, nc2));
                }
            }
        }
        
        dp[r][c1][c2] += c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        return dp[r][c1][c2];
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        m = grid.size();
        n = grid[0].size();
        return dfs(grid, 0, 0, n - 1);
    }
};
