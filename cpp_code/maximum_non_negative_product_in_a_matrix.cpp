/*
1594. Maximum Non Negative Product in a Matrix
https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/

You are given a rows x cols matrix grid.
Initially, you are located at the top-left corner (0, 0), and in each step,
you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (rows - 1, cols - 1),
find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.

Return the maximum non-negative product modulo 109 + 7.
If the maximum product is negative return -1.
Notice that the modulo is performed after getting the maximum product.

Example 1:
Input: grid = [[-1,-2,-3],
               [-2,-3,-3],
               [-3,-3,-2]]
Output: -1
Explanation: It's not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.

Example 2:
Input: grid = [[1,-2,1],
               [1,-2,1],
               [3,-4,1]]
Output: 8
Explanation: Maximum non-negative product is in bold (1 * 1 * -2 * -4 * 1 = 8).

Example 3:
Input: grid = [[1, 3],
               [0,-4]]
Output: 0
Explanation: Maximum non-negative product is in bold (1 * 0 * -4 = 0).

Example 4:
Input: grid = [[ 1, 4,4,0],
               [-2, 0,0,1],
               [ 1,-1,1,1]]
Output: 2
Explanation: Maximum non-negative product is in bold (1 * -2 * 1 * -1 * 1 * 1 = 2).

Constraints:
1 <= rows, cols <= 15
-4 <= grid[i][j] <= 4
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
#include <stdio.h>
#include <map>
using namespace std;
/*
1. Keep track of two DP vectors, mx and mn
2. update mx and mn based on the current number in grid (positive or negative)
3. if current number is positive, use mx. else use mn
*/
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int MOD = 1e9 + 7;
        // we use long long to avoid overflow
        vector<vector<long long>>mx(m,vector<long long>(n)), mn(m,vector<long long>(n));
        mx[0][0] = mn[0][0] = grid[0][0];

        // initialize the top and left sides
        for (int i = 1; i < m; i++) {
            mn[i][0] = mx[i][0] = mx[i - 1][0] * grid[i][0];
        }
        for (int j = 1; j < n; j++) {
            mn[0][j] = mx[0][j] = mx[0][j - 1] * grid[0][j];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] < 0) { // minimum product * negative number = new maximum product
                    mx[i][j] = (min(mn[i - 1][j], mn[i][j - 1]) * grid[i][j]);
                    mn[i][j] = (max(mx[i - 1][j], mx[i][j - 1]) * grid[i][j]);
                }
                else{ // maximum product * positive number = new maximum product
                    mx[i][j] = (max(mx[i-1][j], mx[i][j-1]) * grid[i][j]);
                    mn[i][j] = (min(mn[i-1][j], mn[i][j-1]) * grid[i][j]);
                }
            }
        }

        int ans = mx[m-1][n-1] % MOD;
        return ans < 0 ? -1 : ans;
    }
};
