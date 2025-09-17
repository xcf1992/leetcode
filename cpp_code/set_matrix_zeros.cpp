/*
73. Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:

Input:
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output:
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
Example 2:

Input:
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output:
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]
Follow up:

A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
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
#include <set>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return;
        }
        int n = matrix[0].size();

        int start = 1;
        if (matrix[0][0] == 0) {
            start = 0;
        }
        int startrow = 1;
        int startcolumn = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
                if (i == 0) {
                    startrow = 0;
                }
                if (j == 0) {
                    startcolumn = 0;
                }
            }
        }

        for (int j = 1; j < n; ++j) if (matrix[0][j] == 0) {
            for (int i = 0; i < m; ++i) {
                matrix[i][j] = 0;
            }
        }
        for (int i = 1; i < m; i++) if (matrix[i][0] == 0) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 0;
            }
        }

        if (start == 0) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
        if (startrow == 0) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        if (startcolumn == 0) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};
