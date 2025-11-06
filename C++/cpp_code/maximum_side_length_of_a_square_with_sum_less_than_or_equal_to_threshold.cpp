/*
1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold
https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/

Given a m x n matrix mat and an integer threshold.
Return the maximum side-length of a square with a sum less than or equal to threshold
or return 0 if there is no such square.

Example 1:
1 1 3 2 4 3 2
1 1 3 2 4 3 2
1 1 3 2 4 3 2
Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.

Example 2:
Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0

Example 3:
Input: mat = [[1,1,1,1],[1,0,0,0],[1,0,0,0],[1,0,0,0]], threshold = 6
Output: 3

Example 4:
Input: mat = [[18,70],[61,1],[25,85],[14,40],[11,96],[97,96],[63,45]], threshold = 40184
Output: 2

Constraints:
1 <= m, n <= 300
m == mat.length
n == mat[i].length
0 <= mat[i][j] <= 10000
0 <= threshold <= 10^5
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;

    bool check(int len, int threshold, vector<vector<int>>& sum) {
        for (int i = len; i <= m; ++i) {
            for (int j = len; j <= n; ++j) {
                if (sum[i][j] - sum[i - len][j] - sum[i][j - len] + sum[i - len][j - len] <= threshold) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        m = mat.size();
        if (m == 0) {
            return 0;
        }
        n = mat[0].size();

        vector<vector<int>> preSum(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                preSum[i][j] = mat[i - 1][j - 1] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }

        int left = 0;
        int right = min(m, n);
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid, threshold, preSum)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return right;
    }
};
