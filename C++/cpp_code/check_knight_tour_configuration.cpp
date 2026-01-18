/*
https://leetcode.com/problems/check-knight-tour-configuration/description/
2596. Check Knight Tour Configuration

There is a knight on an n x n chessboard. In a valid configuration, the knight starts at the top-left cell of the board
and visits every cell on the board exactly once.

You are given an n x n integer matrix grid consisting of distinct integers from the range [0, n * n - 1] where
grid[row][col] indicates that the cell (row, col) is the grid[row][col]th cell that the knight visited. The moves are
0-indexed.

Return true if grid represents a valid configuration of the knight's movements or false otherwise.

Note that a valid knight move consists of moving two squares vertically and one square horizontally, or two squares
horizontally and one square vertically. The figure below illustrates all the possible eight moves of a knight from some
cell.




Example 1:


Input: grid = [[0,11,16,5,20],[17,4,19,10,15],[12,1,8,21,6],[3,18,23,14,9],[24,13,2,7,22]]
Output: true
Explanation: The above diagram represents the grid. It can be shown that it is a valid configuration.
Example 2:


Input: grid = [[0,3,6],[5,8,1],[2,7,4]]
Output: false
Explanation: The above diagram represents the grid. The 8th move of the knight is not valid considering its position
after the 7th move.


Constraints:

n == grid.length == grid[i].length
3 <= n <= 7
0 <= grid[row][col] < n * n
All integers in grid are unique.
*/
#include <iostream>
#include <sstream>
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
    vector<vector<int>> movement = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

    bool is_valid(int cur_row, int cur_col, int pre_row, int pre_col) {
        for (int i = 0; i < movement.size(); i++) {
            if (cur_row == pre_row + movement[i][0] && cur_col == pre_col + movement[i][1]) {
                return true;
            }
        }
        return false;
    }
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        vector<pair<int, int>> pos_order;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pos_order.push_back({grid[i][j], i * n + j});
            }
        }
        sort(pos_order.begin(), pos_order.end());

        if (pos_order[0].second != 0) {
            return false;
        }

        int k = pos_order.size();
        for (int i = 1; i < k; i++) {
            int cur_pos = pos_order[i].second;
            int cur_row = cur_pos / n;
            int cur_col = cur_pos % n;
            int pre_pos = pos_order[i - 1].second;
            int pre_row = pre_pos / n;
            int pre_col = pre_pos % n;
            if (!is_valid(cur_row, cur_col, pre_row, pre_col)) {
                return false;
            }
        }
        return true;
    }
};