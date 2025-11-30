/*
1277. Count Square Submatrices with All Ones
https://leetcode.com/problems/count-square-submatrices-with-all-ones/

Given a m * n matrix of ones and zeros,
return how many square submatrices have all ones.

Example 1:
Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation:
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:
Input: matrix =
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation:
There are 6 squares of side 1.
There is 1 square of side 2.
Total number of squares = 6 + 1 = 7.

Constraints:
1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1
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
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();

        int result = 0;
        vector<vector<int>> maxLen(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
            if (matrix[i][0] == 1) {
                maxLen[i][0] = 1;
                result += 1;
            }
        for (int j = 1; j < n; ++j)
            if (matrix[0][j] == 1) {
                maxLen[0][j] = 1;
                result += 1;
            }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                if (matrix[i][j] == 1) {
                    maxLen[i][j] = 1 + min(maxLen[i - 1][j - 1], min(maxLen[i - 1][j], maxLen[i][j - 1]));
                    result += maxLen[i][j];
                }
        }
        return result;
    }
};