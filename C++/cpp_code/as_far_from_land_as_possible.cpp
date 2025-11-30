/*
1162. As Far from Land as Possible
Given an N x N grid containing only values 0 and 1,
where 0 represents water and 1 represents land,
find a water cell such that its distance to the nearest land cell is maximized and return the distance.

The distance used in this problem is the Manhattan distance:
the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

If no land or water exists in the grid, return -1.

Example 1:
1   0   1
0   0   0
1   0   1
Input: [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation:
The cell (1, 1) is as far as possible from all the land with distance 2.

Example 2:
1   0   0
0   0   0
0   0   0
Input: [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation:
The cell (2, 2) is as far as possible from all the land with distance 4.


Note:

1 <= grid.length == grid[0].length <= 100
grid[i][j] is 0 or 1
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
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<long>> dp(m, vector<long>(n, INT_MAX));
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                    count += 1;
                }
        }
        if (count == 0 or count == m * n) {
            return -1;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 0) {
                    if (i > 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                    }
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                }
        }

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j)
                if (grid[i][j] == 0) {
                    if (i < m - 1) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                    if (j < n - 1) {
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                    }
                }
        }

        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 0 and dp[i][j] < INT_MAX) {
                    result = max(result, (int)dp[i][j]);
                }
        }
        return result;
    }
};

class Solution1 {
    // TLE
private:
    int getMinDis(vector<int> cell, vector<vector<int>>& islands) {
        int distance = INT_MAX;
        for (vector<int>& island : islands) {
            distance = min(distance, abs(island[0] - cell[0]) + abs(island[1] - cell[1]));
        }
        return distance;
    }

public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> islands;
        vector<vector<int>> water;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    islands.push_back({i, j});
                } else {
                    water.push_back({i, j});
                }
            }
        }

        if (water.empty() or islands.empty()) {
            return -1;
        }

        int result = 0;
        for (vector<int>& cell : water) {
            result = max(result, getMinDis(cell, islands));
        }
        return result;
    }
};