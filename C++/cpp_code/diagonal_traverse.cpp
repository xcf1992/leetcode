/*
498. Diagonal Traverse
https://leetcode.com/problems/diagonal-traverse/

Given a matrix of M x N elements (M rows, N columns),
return all elements of the matrix in diagonal order as shown in the below image.

Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation:

Note:
The total number of elements of the given matrix will not exceed 10,000.
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
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();

        vector<pair<int, int>> stk;
        stk.push_back({0, 0});
        vector<int> result;
        int step = 1;
        while (!stk.empty()) {
            vector<pair<int, int>> next;
            vector<int> cur;
            for (int k = 0; k < stk.size(); ++k) {
                int i = stk[k].first;
                int j = stk[k].second;
                cur.push_back(matrix[i][j]);

                if (j == 0 and i + 1 < m) {
                    next.push_back({i + 1, j});
                }
                if (j + 1 < n) {
                    next.push_back({i, j + 1});
                }
            }
            stk = next;

            int start = step == 1 ? 0 : cur.size() - 1;
            int end = step == 1 ? cur.size() - 1 : 0;
            int diff = step == 1 ? 1 : -1;
            for (int i = start; (step == 1 and i <= end) or (step == 0 and i >= end); i += diff) {
                result.push_back(cur[i]);
            }
            step = 1 - step;
        }
        return result;
    }
};

class Solution1 {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size();
        if (m == 0) {
            return result;
        }
        int n = matrix[0].size();
        int i = 0;
        int j = 0;
        int backward = 0;

        while (result.size() < m * n) {
            result.push_back(matrix[i][j]);

            if (backward == 0) {
                i--;
                j++;
                if (i < 0 and j <= n - 1) {
                    backward = 1;
                    i += 1;
                } else if (j > n - 1) {
                    backward = 1;
                    i += 2;
                    j = n - 1;
                }
            } else {
                i++;
                j--;
                if (j < 0 and i <= m - 1) {
                    backward = 0;
                    j += 1;
                } else if (i > m - 1) {
                    backward = 0;
                    j += 2;
                    i = m - 1;
                }
            }
        }

        return result;
    }
};