/*
329. Longest Increasing Path in a Matrix
https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down.
You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:
Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:
Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
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
#include <map>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;

    int dfs(vector<vector<int>>& matrix, vector<vector<int>>& memo, int row, int col) {
        if (memo[row][col] != 0) {
            return memo[row][col];
        }

        memo[row][col] = 1;
        vector<int> diff({0, 1, 0, -1, 0});
        for (int i = 0; i < 4; ++i) {
            int nr = row + diff[i];
            int nc = col + diff[i + 1];
            if (nr < 0 or nc < 0 or nr >= m or nc >= n or matrix[nr][nc] <= matrix[row][col]) {
                continue;
            }
            memo[row][col] = max(memo[row][col], 1 + dfs(matrix, memo, nr, nc));
        }
        return memo[row][col];
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        if (m == 0) {
            return 0;
        }
        n = matrix[0].size();

        vector<vector<int>> memo(m, vector<int>(n, 0));
        int result = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = max(result, dfs(matrix, memo, i, j));
            }
        }
        return result;
    }
};