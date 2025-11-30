/*
https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/description/
3197. Find the Minimum Area to Cover All Ones II
You are given a 2D binary array grid.
You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides
such that all the 1's in grid lie inside these rectangles.

Return the minimum possible sum of the area of these rectangles.
Note that the rectangles are allowed to touch.

Example 1:
Input: grid = [[1,0,1],[1,1,1]]
Output: 5
Explanation:
The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
The 1 at (1, 1) is covered by a rectangle of area 1.

Example 2:
Input: grid = [[1,0,1,0],[0,1,0,1]]
Output: 5
Explanation:
The 1's at (0, 0) and (0, 2) are covered by a rectangle of area 3.
The 1 at (1, 1) is covered by a rectangle of area 1.
The 1 at (1, 3) is covered by a rectangle of area 1.

Constraints:
1 <= grid.length, grid[i].length <= 30
grid[i][j] is either 0 or 1.
The input is generated such that there are at least three 1's in grid.
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int minimumSum(vector<vector<int>>& grid) {
        vector<vector<int>> rgrid = rotate(grid);
        return min(solve(grid), solve(rgrid));
    }

private:
    int solve(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int res = n * m;
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 0; j + 1 < m; j++) {
                res = min(res, calc(grid, 0, i, 0, m - 1) + calc(grid, i + 1, n - 1, 0, j) +
                                       calc(grid, i + 1, n - 1, j + 1, m - 1));
                res = min(res,
                          calc(grid, 0, i, 0, j) + calc(grid, 0, i, j + 1, m - 1) + calc(grid, i + 1, n - 1, 0, m - 1));
            }
        }
        for (int i = 0; i + 2 < n; i++) {
            for (int j = i + 1; j + 1 < n; j++) {
                res = min(res, calc(grid, 0, i, 0, m - 1) + calc(grid, i + 1, j, 0, m - 1) +
                                       calc(grid, j + 1, n - 1, 0, m - 1));
            }
        }
        return res;
    }

    int calc(vector<vector<int>>& grid, int u, int d, int l, int r) {
        int min_i = grid.size(), max_i = 0;
        int min_j = grid[0].size(), max_j = 0;
        for (int i = u; i <= d; i++) {
            for (int j = l; j <= r; j++) {
                if (grid[i][j] == 1) {
                    min_i = min(min_i, i);
                    min_j = min(min_j, j);
                    max_i = max(max_i, i);
                    max_j = max(max_j, j);
                }
            }
        }
        return min_i <= max_i ? (max_i - min_i + 1) * (max_j - min_j + 1) : INT_MAX / 3;
    }

    vector<vector<int>> rotate(vector<vector<int>>& vec) {
        int n = vec.size();
        int m = vec[0].size();
        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ret[m - j - 1][i] = vec[i][j];
            }
        }
        return ret;
    }
};
