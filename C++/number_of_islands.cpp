/*
200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3
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
#include <set>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    void dfs(vector<vector<char>>& grid, int row, int col) {
        if (row < 0 or col < 0 or row >= m or col >= n or grid[row][col] != '1') {
            return;
        }

        grid[row][col] = '0';
        for (int i = 1; i < diff.size(); ++i) {
            dfs(grid, row + diff[i], col + diff[i - 1]);
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        if (m == 0) {
            return 0;
        }
        n = grid[0].size();

        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    result += 1;
                    dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};
