/*
 Given an integer matrix, find the length of the longest increasing path.
 
 From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
 
 Example 1:
 
 nums = [
 [9,9,4],
 [6,6,8],
 [2,1,1]
 ]
 Return 4
 The longest increasing path is [1, 2, 6, 9].
 
 Example 2:
 
 nums = [
 [3,4,5],
 [3,2,6],
 [2,2,1]
 ]
 Return 4
 The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
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
    bool update(vector<vector<int>>& matrix, vector<vector<int>>& dp, int& result) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool updated = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j - 1 >= 0 && matrix[i][j] > matrix[i][j - 1] && dp[i][j - 1] + 1 > dp[i][j]) {
                    dp[i][j] = dp[i][j - 1] + 1;
                    updated = true;
                }
                
                if (i - 1 >= 0 && matrix[i][j] > matrix[i - 1][j] && dp[i - 1][j] + 1 > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j] + 1;
                    updated = true;
                }
                
                if (j + 1 < n && matrix[i][j] > matrix[i][j + 1] && dp[i][j + 1] + 1 > dp[i][j]) {
                    dp[i][j] = dp[i][j + 1] + 1;
                    updated = true;
                }
                
                if (i + 1 < m && matrix[i][j] > matrix[i + 1][j] && dp[i + 1][j] + 1 > dp[i][j]) {
                    dp[i][j] = dp[i + 1][j] + 1;
                    updated = true;
                }
                result = max(result, dp[i][j]);
            }
        }
        return updated;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 1));
        int result = 0;
        while (update(matrix, dp, result)) {
        }
        return result;
    }
};

class Solution1 {
private:
    int update(vector<vector<int>>& matrix, int x, int y, int val, vector<vector<int>>& dp) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (x < 0 || y < 0 || x >= m || y >= n || matrix[x][y] <= val) {
            return 0;
        }
        
        if (dp[x][y] != 0) {
            return dp[x][y];
        }
        
        dp[x][y] = max(dp[x][y], update(matrix, x + 1, y, matrix[x][y], dp) + 1);
        dp[x][y] = max(dp[x][y], update(matrix, x - 1, y, matrix[x][y], dp) + 1);
        dp[x][y] = max(dp[x][y], update(matrix, x, y + 1, matrix[x][y], dp) + 1);
        dp[x][y] = max(dp[x][y], update(matrix, x, y - 1, matrix[x][y], dp) + 1);
        return dp[x][y];
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result = max(result, update(matrix, i, j, INT_MIN, dp));
            }
        }
        return result;
    }
};
