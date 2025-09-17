/*
931. Minimum Falling Path Sum
https://leetcode.com/problems/minimum-falling-path-sum/

Given a square array of integers A,
we want the minimum sum of a falling path through A.

A falling path starts at any element in the first row,
and chooses one element from each row.
The next row's choice must be in a column that is different from the previous row's column by at most one.

Example 1:
Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: 12
Explanation:
The possible falling paths are:
[1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
[2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
[3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
The falling path with the smallest sum is [1,4,7], so the answer is 12.

Note:
1 <= A.length == A[0].length <= 100
-100 <= A[i][j] <= 100
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
#include <numeric>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int m = A.size();
        if (m == 0) {
            return 0;
        }
        int n = A[0].size();

        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        dp[0] = A[0];

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int c = -1; c <= 1; c++) {
                    if (j + c >= 0 and j + c < n) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j + c] + A[i][j]);
                    }
                }
            }
        }

        int result = INT_MAX;
        for (int num : dp[m - 1]) {
            result = min(result, num);
        }
        return result;
    }
};
