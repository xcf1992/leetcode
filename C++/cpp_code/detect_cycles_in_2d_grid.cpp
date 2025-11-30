/*
1559. Detect Cycles in 2D Grid
https://leetcode.com/problems/detect-cycles-in-2d-grid/

Given a 2D array of characters grid of size m x n,
you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell.
From a given cell, you can move to one of the cells adjacent to it -
in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move.
For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last
visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

Example 1:
Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:
Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

Example 3:
Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false

Constraints:
m == grid.length
n == grid[i].length
1 <= m <= 500
1 <= n <= 500
grid consists only of lowercase English letters.
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
#include <climits>
#include <map>
using namespace std;

class Solution {
private:
    vector<int> dir = {0, 1, 0, -1, 0};

    bool isCyclic(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j, int x, int y) {
        visited[i][j] = true;
        for (int d = 0; d < 4; ++d) {
            int a = i + dir[d];
            int b = j + dir[d + 1];
            if (a >= 0 and a < grid.size() and b >= 0 and b < grid[0].size() and grid[a][b] == grid[i][j] and
                !(x == a and y == b)) {
                if (visited[a][b] or isCyclic(grid, visited, a, b, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                if (!visited[i][j] and isCyclic(grid, visited, i, j, -1, -1)) {
                    return true;
                }
        }
        return false;
    }
};