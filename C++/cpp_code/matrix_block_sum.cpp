/*
1314. Matrix Block Sum
https://leetcode.com/problems/matrix-block-sum/

Given a m * n matrix mat and an integer K,
return a matrix answer where each answer[i][j] is the sum of all elements
mat[r][c] for i - K <= r <= i + K, j - K <= c <= j + K,
and (r, c) is a valid position in the matrix.

Example 1:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]

Example 2:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n, K <= 100
1 <= mat[i][j] <= 100
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<vector<int> > matrixBlockSum(vector<vector<int> > &mat, int K) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int> > preSum(m, vector<int>(n, 0));
        preSum[0][0] = mat[0][0];
        for (int i = 1; i < m; ++i) {
            preSum[i][0] = preSum[i - 1][0] + mat[i][0];
        }
        for (int j = 1; j < n; ++j) {
            preSum[0][j] = preSum[0][j - 1] + mat[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                preSum[i][j] = mat[i][j] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }

        vector<vector<int> > result(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int rMin = max(0, i - K);
                int rMax = min(m - 1, i + K);
                int cMin = max(0, j - K);
                int cMax = min(n - 1, j + K);

                int v1 = (cMin - 1 >= 0 ? preSum[rMax][cMin - 1] : 0);
                int v2 = (rMin - 1 >= 0 ? preSum[rMin - 1][cMax] : 0);
                int v3 = (cMin - 1 >= 0
                and rMin
                -1 >= 0 ? preSum[rMin - 1][cMin - 1] : 0
                )
                ;
                result[i][j] = preSum[rMax][cMax] - v1 - v2 + v3;
            }
        }
        return result;
    }
};