/*
 417. Pacific Atlantic Water Flow
 Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
 the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

 Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

 Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

 Note:
 The order of returned grid coordinates does not matter.
 Both m and n are less than 150.
 Example:

 Given the following 5x5 matrix:

 Pacific ~   ~   ~   ~   ~
 ~  1   2   2   3  (5) *
 ~  3   2   3  (4) (4) *
 ~  2   4  (5)  3   1  *
 ~ (6) (7)  1   4   5  *
 ~ (5)  1   1   2   4  *
 *   *   *   *   * Atlantic

 Return:

 [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
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
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    void canFlow(vector<vector<int>>& matrix, vector<vector<int>>& reached, int r, int c, int height, int mark) {
        if (r >= m or c >= n or r < 0 or c < 0 or matrix[r][c] < height or (reached[r][c] & mark) != 0) {
            return;
        }

        reached[r][c] |= mark;
        for (int i = 1; i < diff.size(); ++i) {
            canFlow(matrix, reached, r + diff[i], c + diff[i - 1], matrix[r][c], mark);
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        m = matrix.size();
        if (m == 0) {
            return {};
        }
        n = matrix[0].size();

        vector<vector<int>> reached(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            canFlow(matrix, reached, i, 0, INT_MIN, 1);
            canFlow(matrix, reached, i, n - 1, INT_MIN, 2);
        }
        for (int j = 0; j < n; ++j) {
            canFlow(matrix, reached, 0, j, INT_MIN, 1);
            canFlow(matrix, reached, m - 1, j, INT_MIN, 2);
        }

        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (reached[i][j] == 3) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
};
