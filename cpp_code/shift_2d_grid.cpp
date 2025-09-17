/*
1260. Shift 2D Grid
https://leetcode.com/problems/shift-2d-grid/

Given a 2D grid of size n * m and an integer k.
You need to shift the grid k times.

In one shift operation:
Element at grid[i][j] becomes at grid[i][j + 1].
Element at grid[i][m - 1] becomes at grid[i + 1][0].
Element at grid[n - 1][m - 1] becomes at grid[0][0].
Return the 2D grid after applying shift operation k times.

Example 1:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]

Example 2:
Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

Example 3:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]

Constraints:
1 <= grid.length <= 50
1 <= grid[i].length <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
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
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        if (m == 0) {
            return grid;
        }
        int n = grid[0].size();

        vector<vector<int>> result(m, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            int nj = (j + k) % n;
            int row = (j + k) / n;
            for (int k = 0; k < m; ++k) {
                result[(row + k) % m][nj] = grid[k][j];
            }
        }
        return result;
    }
};
