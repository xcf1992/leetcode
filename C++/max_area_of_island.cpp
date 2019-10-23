/*
695. Max Area of Island
https://leetcode.com/problems/max-area-of-island/

Given a non-empty 2D array grid of 0's and 1's,
an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array.
(If there is no island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.

Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.
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
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    void check(int r, int c, int& area, vector<vector<int>>& grid) {
        if (r < 0 or r >= m or c < 0 or c >= n or grid[r][c] != 1) {
            return;
        }

        area += 1;
        grid[r][c] = -1;
        for (int i = 1; i < diff.size(); ++i) {
            check(r + diff[i], c + diff[i - 1], area, grid);
        }
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) if (grid[i][j] == 1) {
                int area = 0;
                check(i, j, area, grid);
                result = max(area, result);
            }
        }
        return result;
    }
};
