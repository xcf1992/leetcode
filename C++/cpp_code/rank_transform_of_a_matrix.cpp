/*
1632. Rank Transform of a Matrix
https://leetcode.com/problems/rank-transform-of-a-matrix/

Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].

The rank is an integer that represents how large an element is compared to other elements.
It is calculated using the following rules:
The rank is an integer starting from 1.
If two elements p and q are in the same row or column, then:
If p < q then rank(p) < rank(q)
If p == q then rank(p) == rank(q)
If p > q then rank(p) > rank(q)
The rank should be as small as possible.
It is guaranteed that answer is unique under the given rules.

Example 1:
Input: matrix = [[1,2],[3,4]]
Output: [[1,2],[2,3]]
Explanation:
The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1]
and matrix[1][0] are rank 2.

Example 2:
Input: matrix = [[7,7],[7,7]]
Output: [[1,1],[1,1]]

Example 3:
Input: matrix = [[20,-21,14],[-19,4,19],[22,-47,24],[-19,4,19]]
Output: [[4,2,3],[1,3,4],[5,1,6],[1,3,4]]

Example 4:
Input: matrix = [[7,3,6],[1,4,5],[9,8,2]]
Output: [[5,1,4],[1,2,3],[6,3,1]]

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 500
-109 <= matrix[row][col] <= 109
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int find(vector<int>& root, int x) {
        if (root[x] != x) {
            root[x] = find(root, root[x]);
        }
        return root[x];
    }

public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        map<int, vector<int>> mp;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                mp[matrix[i][j]].push_back(i * n + j);
            }
        }

        vector<int> rank(m + n, 0);
        vector<vector<int>> res(m, vector<int>(n));
        for (auto& it : mp) {
            vector<int> root(m + n, 0);
            iota(begin(root), end(root), 0);

            auto& v = it.second;
            for (auto& a : v) {
                int i = a / n, j = a % n;
                int r1 = find(root, i), r2 = find(root, j + m);
                root[r1] = r2;  // make row point to column
                rank[r2] = max(rank[r1], rank[r2]);
            }

            auto rank2 = rank;
            for (auto& a : v) {
                int i = a / n, j = a % n;
                int r = find(root, i);
                res[i][j] = rank[r] + 1;
                rank2[i] = rank[r] + 1;
                rank2[j + m] = rank[r] + 1;
            }

            rank = move(rank2);
        }
        return res;
    }
};