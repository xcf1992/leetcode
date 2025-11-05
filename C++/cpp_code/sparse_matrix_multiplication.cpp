/*
311. Sparse Matrix Multiplication
https://leetcode.com/problems/sparse-matrix-multiplication/

Given two sparse matrices A and B,
return the result of AB.
You may assume that A's column number is equal to B's row number.

Example:
A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]
B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]
     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
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
/*
The idea is derived from a CMU lecture.
http://www.cs.cmu.edu/~scandal/cacm/node9.html

A sparse matrix can be represented as a sequence of rows,
each of which is a sequence of (column-number, value) pairs of the nonzero values in the row.

So let's create a non-zero array for A, and do multiplication on B.
*/
class Solution {
public:
    vector<vector<int> > multiply(vector<vector<int> > &A, vector<vector<int> > &B) {
        int m = A.size();
        int n = A[0].size();
        vector<vector<pair<int, int> > > indexA(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (A[i][j] != 0) {
                    indexA[i].push_back({j, A[i][j]});
                }
        }

        int nb = B[0].size();
        vector<vector<int> > result(m, vector<int>(nb, 0));
        for (int i = 0; i < m; ++i) {
            vector<pair<int, int> > nonZero = indexA[i];
            for (pair<int, int> &index: nonZero) {
                int j = index.first;
                int val = index.second;
                for (int k = 0; k < nb; ++k) {
                    result[i][k] += val * B[j][k];
                }
            }
        }
        return result;
    }
};

class Solution1 {
    // 20.08% brute force
public:
    vector<vector<int> > multiply(vector<vector<int> > &A, vector<vector<int> > &B) {
        int m = A.size();
        int n = A[0].size();
        vector<vector<int> > result(m, vector<int>(B[0].size(), 0));
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < n; k++)
                if (A[i][k] != 0) {
                    for (int j = 0; j < B[0].size(); j++)
                        if (B[k][j] != 0) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                }
        }
        return result;
    }
};