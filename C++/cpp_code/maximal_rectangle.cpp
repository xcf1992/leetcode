/*
85. Maximal Rectangle
https://leetcode.com/problems/maximal-rectangle/

Given a 2D binary matrix filled with 0's and 1's,
find the largest rectangle containing only 1's and return its area.

Example:
Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
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
using namespace std;

class Solution {
    // O(M * N)
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();

        vector<int> height(n, 0); // store the height of current column
        vector<int> left(n, 0); // store the left most column has the same height of col j
        vector<int> right(n, n); // store the right most column has the same height of col j
        int result = 0;
        for (int i = 0; i < m; ++i) {
            int curLeft = 0;
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    height[j] += 1;
                    /*
                    * Consider what causes changes to the left bound of our rectangle.
                    * Since all instances of zeros occurring in the row above the current one have already been factored into the current version of left,
                    * the only thing that affects our left is if we encounter a zero in our current row.
                    */
                    left[j] = max(left[j], curLeft);
                } else {
                    height[j] = 0;
                    /*
                    * cur_left is one greater than rightmost occurrence of zero we have encountered.
                    * When we "expand" the rectangle to the left, we know it can't expand past that point,
                    * otherwise it'll run into the zero.
                    */
                    left[j] = 0;
                    curLeft = j + 1;
                }
            }
            int curRight = n;
            for (int j = n - 1; j >= 0; --j) {
                if (matrix[i][j] == '1') {
                    right[j] = min(right[j], curRight);
                } else {
                    right[j] = n;
                    curRight = j;
                }
            }

            for (int j = 0; j < n; ++j) {
                result = max(result, height[j] * (right[j] - left[j]));
            }
        }
        return result;
    }
};

class Solution1 {
    // 50% O(M * N * N)
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        // consecutiveOne[i][j] means number of consecutive ones from matrix[i][j] to its left
        vector<vector<int> > consecutiveOne(m, vector<int>(n, 0));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '0') {
                    consecutiveOne[i][j] = 0;
                } else {
                    consecutiveOne[i][j] = j == 0 ? 1 : consecutiveOne[i][j - 1] + 1;
                }

                int len = consecutiveOne[i][j];
                for (int k = i; k >= 0; --k) {
                    if (consecutiveOne[k][j] == 0) {
                        break;
                    }
                    len = min(len, consecutiveOne[k][j]);
                    result = max(result, (i - k + 1) * len);
                }
            }
        }
        return result;
    }
};