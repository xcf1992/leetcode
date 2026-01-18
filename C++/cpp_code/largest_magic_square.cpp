/*
https://leetcode.com/problems/largest-magic-square/description
1895. Largest Magic Square

A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal
sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic
square.

Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found
within this grid.



Example 1:


Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
Output: 3
Explanation: The largest magic square has a size of 3.
Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
- Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
- Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
- Diagonal sums: 5+4+3 = 6+4+2 = 12
Example 2:


Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
Output: 2


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 106
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
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // prefix sum of each row
        vector<vector<int>> row_sum(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            row_sum[i][0] = grid[i][0];
            for (int j = 1; j < n; ++j) {
                row_sum[i][j] = row_sum[i][j - 1] + grid[i][j];
            }
        }

        // prefix sum of each column
        vector<vector<int>> col_sum(m, vector<int>(n));
        for (int j = 0; j < n; ++j) {
            col_sum[0][j] = grid[0][j];
            for (int i = 1; i < m; ++i) {
                col_sum[i][j] = col_sum[i - 1][j] + grid[i][j];
            }
        }

        // enumerate edge lengths from largest to smallest
        for (int len = min(m, n); len >= 2; --len) {
            // enumerate the top-left corner position (i,j) of the square
            for (int i = 0; i + len <= m; ++i) {
                for (int j = 0; j + len <= n; ++j) {
                    // the value for each row, column, and diagonal should be
                    // calculated (using the first row as a sample)
                    int std_sum = row_sum[i][j + len - 1] - (j ? row_sum[i][j - 1] : 0);
                    bool valid = true;
                    // enumerate each row and directly compute the sum using
                    // prefix sums since we have already used the first line as
                    // a sample, we can skip the first line here.
                    for (int ii = i + 1; ii < i + len; ++ii) {
                        if (row_sum[ii][j + len - 1] - (j ? row_sum[ii][j - 1] : 0) != std_sum) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) {
                        continue;
                    }
                    // enumerate each column and directly calculate the sum
                    // using prefix sums
                    for (int jj = j; jj < j + len; ++jj) {
                        if (col_sum[i + len - 1][jj] - (i ? col_sum[i - 1][jj] : 0) != std_sum) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) {
                        continue;
                    }
                    // d1 and d2 represent the sums of the two diagonals
                    // respectively. here d denotes diagonal
                    int d1 = 0, d2 = 0;
                    // sum directly by traversing without using the prefix sum.
                    for (int k = 0; k < len; ++k) {
                        d1 += grid[i + k][j + k];
                        d2 += grid[i + k][j + len - 1 - k];
                    }

                    if (d1 == std_sum && d2 == std_sum) {
                        return len;
                    }
                }
            }
        }

        return 1;
    }
};
