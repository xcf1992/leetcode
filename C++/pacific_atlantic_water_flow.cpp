/*
 Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
 
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
    void canFlow(vector<vector<int>>& matrix, vector<vector<bool>>& flowTo, int i, int j, int height) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        if (i >= m || j >= n || i < 0 || j < 0 || flowTo[i][j] || matrix[i][j] > height) {
            return;
        }
        
        flowTo[i][j] = true;
        canFlow(matrix, flowTo, i - 1, j, matrix[i][j]);
        canFlow(matrix, flowTo, i + 1, j, matrix[i][j]);
        canFlow(matrix, flowTo, i, j - 1, matrix[i][j]);
        canFlow(matrix, flowTo, i, j + 1, matrix[i][j]);
        return;
    }
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();
        
        vector<vector<bool>> flow2P(m, vector<bool>(n, false));
        vector<vector<bool>> flow2A(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            canFlow(matrix, flow2A, i, 0, INT_MIN);
            canFlow(matrix, flow2P, i, n - 1, INT_MIN);
        }
        for (int j = 0; j < n; j++) {
            canFlow(matrix, flow2A, 0, j, INT_MIN);
            canFlow(matrix, flow2P, m - 1, j, INT_MIN);
        }
        
        vector<pair<int, int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (flow2P[i][j] && flow2A[i][j]) {
                    result.push_back(make_pair(i, j));
                }
            }
        }
        return result;
    }
};
