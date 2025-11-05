/*
1428. Leftmost Column with at Least a One
https://leetcode.com/problems/leftmost-column-with-at-least-a-one/

(This problem is an interactive problem.)

A binary matrix means that all elements are 0 or 1.
For each individual row of the matrix, this row is sorted in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix,
return leftmost column index(0-indexed) with at least a 1 in it.
If such index doesn't exist, return -1.

You can't access the Binary Matrix directly.
You may only access the matrix using a BinaryMatrix interface:

BinaryMatrix.get(row, col) returns the element of the matrix at index (row, col) (0-indexed).
BinaryMatrix.dimensions() returns a list of 2 elements [rows, cols],
which means the matrix is rowscols.
Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.
Also, any solutions that attempt to circumvent the judge will result in disqualification.

For custom testing purposes you're given the binary matrix mat as input in the following four examples.
You will not have access the binary matrix directly.

Example 1:
0 0
1 1
Input: mat = [[0,0],[1,1]]
Output: 0

Example 2:
Input: mat = [[0,0],[0,1]]
Output: 1

Example 3:
Input: mat = [[0,0],[0,0]]
Output: -1

Example 4:
Input: mat = [[0,0,0,1],[0,0,1,1],[0,1,1,1]]
Output: 1

Constraints:
rows == mat.length
cols == mat[i].length
1 <= rows, cols <= 100
mat[i][j] is either 0 or 1.
mat[i] is sorted in a non-decreasing way.
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

// This is the BinaryMatrix's API interface.
// You should not implement it, or speculate about its implementation
class BinaryMatrix {
public:
    int get(int row, int col);

    vector<int> dimensions();
};

/*
O(M + N)
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        //get the dimensions

		int n = binaryMatrix.dimensions()[0];
        int m = binaryMatrix.dimensions()[1];

		//go as much left as you can, and then go downwards.
        int check = m-1;
        for(int i = 0;i<n;i++){
            while(check>=0 and binaryMatrix.get(i,check)==1){
                check--;
            }
        }
        return (check==m-1)?-1:check+1;
    }
*/
class Solution {
private:
    int m = 0;
    int n = 0;

    int findFirstOne(BinaryMatrix &binaryMatrix, int row) {
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (binaryMatrix.get(row, mid) == 1) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimension = binaryMatrix.dimensions();
        m = dimension[0];
        n = dimension[1];

        int result = n;
        for (int i = 0; i < m; ++i) {
            int col = findFirstOne(binaryMatrix, i);
            if (col != n) {
                result = min(result, col);
            }
        }
        return result == n ? -1 : result;
    }
};