/*
https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/description/
2133. Check if Every Row and Column Contains All Numbers

An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).

Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.



Example 1:


Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
Output: true
Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
Hence, we return true.
Example 2:


Input: matrix = [[1,1,1],[1,2,3],[1,2,3]]
Output: false
Explanation: In this case, n = 3, but the first row and the first column do not contain the numbers 2 or 3.
Hence, we return false.


Constraints:

n == matrix.length == matrix[i].length
1 <= n <= 100
1 <= matrix[i][j] <= n
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // check rows
        for (int i = 0; i < n; i++) {
            vector<int> visited_row(n + 1, 0);
            vector<int> visited_col(n + 1, 0);
            for (int j = 0; j < n; j++) {
                int cur = matrix[i][j];
                if (visited_row[cur] == 0) {
                    visited_row[cur] = 1;
                    visited_row[0] += 1;
                } else {
                    return false;
                }

                cur = matrix[j][i];
                if (visited_col[cur] == 0) {
                    visited_col[cur] = 1;
                    visited_col[0] += 1;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
