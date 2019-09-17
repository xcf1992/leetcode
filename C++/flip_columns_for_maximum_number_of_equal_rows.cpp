/*
1072. Flip Columns For Maximum Number of Equal Rows
https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/

Given a matrix consisting of 0s and 1s,
we may choose any number of columns in the matrix and flip every cell in that column.
Flipping a cell changes the value of that cell from 0 to 1 or from 1 to 0.
Return the maximum number of rows that have all values equal after some number of flips.

Example 1:
Input: [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:
Input: [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:
Input: [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.

Note:
1 <= matrix.length <= 300
1 <= matrix[i].length <= 300
All matrix[i].length's are equal
matrix[i][j] is 0 or 1
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
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        unordered_map<string, int> count;
        for (int i = 0; i < m; ++i) {
            string key1 = "";
            string key2 = "";
            for (int j = 0; j < n; ++j) {
                key1.push_back(matrix[i][j] + '0');
                key2.push_back(1 - matrix[i][j] + '0');
            }
            count[key1] += 1;
            count[key2] += 1;
        }

        int result = 0;
        for (auto& it: count) {
            result = max(result, it.second);
        }
        return result;
    }
};
