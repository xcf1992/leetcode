/*
https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/description/
3619. Count Islands With Total Value Divisible by K
Medium

You are given an m x n matrix grid and a positive integer k. An island is a group of positive integers (representing
land) that are 4-directionally connected (horizontally or vertically).

The total value of an island is the sum of the values of all cells in the island.

Return the number of islands with a total value divisible by k.



Example 1:


Input: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5

Output: 2

Explanation:

The grid contains four islands. The islands highlighted in blue have a total value that is divisible by 5, while the
islands highlighted in red do not.

Example 2:


Input: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3

Output: 6

Explanation:

The grid contains six islands, each with a total value that is divisible by 3.



Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
0 <= grid[i][j] <= 106
1 <= k <= 106
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
    int m_;
    int n_;
    vector<int> diff_ = {0, 1, 0, -1, 0};

    void calc_island_size(int k, int row, int col, vector<vector<int>>& grid, int& area) {
        if (row < 0 || row >= m_ || col < 0 || col >= n_) {
            return;
        }

        if (grid[row][col] == 0) {
            return;
        }

        area = ((grid[row][col] % k) + area) % k;
        grid[row][col] = 0;
        for (int i = 0; i < 4; i++) {
            int nxt_row = row + diff_[i];
            int nxt_col = col + diff_[i + 1];
            calc_island_size(k, nxt_row, nxt_col, grid, area);
        }
    }
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        m_ = grid.size();
        n_ = grid[0].size();

        int rst = 0;
        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                if (grid[i][j] == 0) {
                    continue;
                }

                int area = 0;
                calc_island_size(k, i, j, grid, area);
                if (area % k == 0) {
                    rst += 1;
                }
            }
        }
        return rst;
    }
};
