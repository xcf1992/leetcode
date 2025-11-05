/*
308. Range Sum Query 2D - Mutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1)
and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10

Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.
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

class NumMatrix {
private:
    int M = 0;
    int N = 0;

    vector<vector<int> > prefixSum;
    vector<vector<int> > mtx;

public:
    NumMatrix(vector<vector<int> > &matrix) {
        M = matrix.size();
        if (M != 0) {
            N = matrix[0].size();
        }
        for (int i = 0; i < M; ++i) {
            vector<int> sum(N, 0);
            sum[0] = matrix[i][0];
            for (int j = 1; j < N; ++j) {
                sum[j] = sum[j - 1] + matrix[i][j];
            }
            prefixSum.push_back(sum);
        }
        mtx = matrix;
    }

    void update(int row, int col, int val) {
        int diff = val - mtx[row][col];
        for (int j = col; j < N; ++j) {
            prefixSum[row][j] += diff;
        }
        mtx[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int result = 0;
        for (int i = row1; i <= row2; ++i) {
            result += prefixSum[i][col2];
            if (col1 != 0) {
                result -= prefixSum[i][col1 - 1];
            }
        }
        return result;
    }
};

/*
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix* obj = new NumMatrix(matrix);
* obj->update(row,col,val);
* int param_2 = obj->sumRegion(row1,col1,row2,col2);
*/