/*
https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/description/
2328. Number of Increasing Paths in a Grid

You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.

Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell.
Since the answer may be very large, return it modulo 109 + 7.

Two paths are considered different if they do not have exactly the same sequence of visited cells.



Example 1:


Input: grid = [[1,1],[3,4]]
Output: 8
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [1], [3], [4].
- Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
- Paths with length 3: [1 -> 3 -> 4].
The total number of paths is 4 + 3 + 1 = 8.
Example 2:

Input: grid = [[1],[2]]
Output: 3
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [2].
- Paths with length 2: [1 -> 2].
The total number of paths is 2 + 1 = 3.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
1 <= grid[i][j] <= 105
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    int mod_ = 1e9 + 7;
    int m_ = 0;
    int n_ = 0;
    vector<int> diff_ = {0, 1, 0, -1, 0};

    long long dfs(int i, int j, vector<vector<int>>& grid, vector<vector<long long>>& dp) {
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        dp[i][j] = 1; // path with len = 1
        for (int k = 0; k < 4; k++) {
            int ni = i + diff_[k];
            int nj = j + diff_[k + 1];
            if (ni < 0 || ni >= m_ || nj < 0 || nj >= n_) {
                continue;
            }

            if (grid[ni][nj] <= grid[i][j]) {
                continue;
            }

            dp[i][j] = (dp[i][j] + dfs(ni, nj, grid, dp)) % mod_;
        }
        return dp[i][j];
    }
public:
    int countPaths(vector<vector<int>>& grid) {
        m_ = grid.size();
        n_ = grid[0].size();
        vector<vector<long long>> dp(m_, vector<long long>(n_, -1));

        long long rst = 0;
        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                rst = (rst + dfs(i, j, grid, dp)) % mod_;
            }
        }
        return rst;
    }
};