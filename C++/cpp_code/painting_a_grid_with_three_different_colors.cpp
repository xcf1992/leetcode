/*
https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description/
1931. Painting a Grid With Three Different Colors
You are given two integers m and n.
Consider an m x n grid where each cell is initially white.
You can paint each cell red, green, or blue. All cells must be painted.

Return the number of ways to color the grid with no two adjacent cells having the same color.
Since the answer can be very large, return it modulo 109 + 7.

Example 1:
Input: m = 1, n = 1
Output: 3
Explanation: The three possible colorings are shown in the image above.

Example 2:
Input: m = 1, n = 2
Output: 6
Explanation: The six possible colorings are shown in the image above.

Example 3:
Input: m = 5, n = 5
Output: 580986

Constraints:
1 <= m <= 5
1 <= n <= 1000
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int colorTheGrid(int m, int n) {
        // 3 ^ 5 = 243
        const int MOD = 1e9 + 7;
        int dp[1005][250] = {0};
        vector<int> good;
        vector<int> pattern[250];
        int total = pow(3, m);
        // generate pattern for each column, and check if it is valid
        for (int i = 0; i < total; i++) {
            int val = i;
            for (int j = 0; j < m; j++) {
                pattern[i].push_back(val % 3);
                val /= 3;
            }

            int valid = 1;
            for (int j = 1; j < m; j++) {
                if (pattern[i][j] == pattern[i][j - 1]) {
                    valid = 0;
                    break;
                }
            }

            if (valid) {
                good.push_back(i);
            }
        }

        // check if two cols could be next to each other
        size_t col_cnt = good.size();
        int row_valid[250][250] = {0};
        for (size_t i = 0; i < col_cnt; i++) {
            int col1 = good[i];
            dp[1][col1] = 1;

            for (size_t j = i + 1; j < col_cnt; j++) {
                int col2 = good[j];
                row_valid[col1][col2] = 1;
                row_valid[col2][col1] = 1;
                for (int k = 0; k < m; k++) {
                    if (pattern[col1][k] == pattern[col2][k]) {
                        row_valid[col1][col2] = 0;
                        row_valid[col2][col1] = 0;
                        break;
                    }
                }
            }
        }

        for (size_t col = 2; col <= n; col++) {
            for (int i : good) {
                for (int j : good) {
                    if (row_valid[i][j]) {
                        dp[col][i] = (dp[col][i] + dp[col - 1][j]) % MOD;
                    }
                }
            }
        }

        int rst = 0;
        for (int i : good) {
            rst = (rst + dp[n][i]) % MOD;
        }
        return rst;
    }
};