/*
https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/description/
1074. Number of Submatrices That Sum to Target

Given a matrix, and a target,
return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different
if they have some coordinate that is different: for example, if x1 != x1'.

Example 1:
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Example 2:
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.

Note:
1 <= matrix.length <= 300
1 <= matrix[0].length <= 300
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8
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
using namespace std;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (vector<int>& row : matrix) {
            for (int i = 1; i < n; ++i) {
                row[i] += row[i - 1];
            }
        }

        int result = 0;
        for (int col1 = 0; col1 < n; col1++) {
            for (int col2 = col1; col2 < n; ++col2) {
                // sumCount stores the freq of sum, which is between col1 and col2, from row 0 to current row
                unordered_map<int, int> sum_cnt;
                sum_cnt[0] = 1;
                int sum = 0;
                for (int row = 0; row < m; row++) {
                    sum += matrix[row][col2] - (col1 == 0 ? 0 : matrix[row][col1 - 1]);
                    result += sum_cnt[sum - target];
                    sum_cnt[sum] += 1;
                }
            }
        }
        return result;
    }
};
