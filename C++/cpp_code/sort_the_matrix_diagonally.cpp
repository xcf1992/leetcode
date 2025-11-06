/*
1329. Sort the Matrix Diagonally
https://leetcode.com/problems/sort-the-matrix-diagonally/

Given a m * n matrix mat of integers,
sort it diagonally in ascending order from the top-left to the bottom-right
then return the sorted array.

Example 1:
Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 100
1 <= mat[i][j] <= 100
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        vector<vector<int>> sortedMat;
        for (int i = m - 1; i >= 0; --i) {
            int r = i;
            int c = 0;
            vector<int> diag;
            while (r < m and c < n) {
                diag.push_back(mat[r][c]);
                r += 1;
                c += 1;
            }
            sortedMat.push_back(diag);
        }
        for (int j = 1; j < n; ++j) {
            int r = 0;
            int c = j;
            vector<int> diag;
            while (r < m and c < n) {
                diag.push_back(mat[r][c]);
                r += 1;
                c += 1;
            }
            sortedMat.push_back(diag);
        }

        for (vector<int>& arr : sortedMat) {
            sort(arr.begin(), arr.end());
        }

        int index = 0;
        for (int i = m - 1; i >= 0; --i) {
            int r = i;
            int c = 0;
            int pos = 0;
            while (r < m and c < n) {
                mat[r][c] = sortedMat[index][pos];
                pos += 1;
                r += 1;
                c += 1;
            }
            index += 1;
        }
        for (int j = 1; j < n; ++j) {
            int r = 0;
            int c = j;
            int pos = 0;
            while (r < m and c < n) {
                mat[r][c] = sortedMat[index][pos];
                pos += 1;
                r += 1;
                c += 1;
            }
            index += 1;
        }
        return mat;
    }
};