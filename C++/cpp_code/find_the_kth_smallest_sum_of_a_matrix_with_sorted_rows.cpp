/*
1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows
https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/

You are given an m * n matrix, mat, and an integer k,
which has its rows sorted in non-decreasing order.

You are allowed to choose exactly 1 element from each row to form an array.
Return the Kth smallest array sum among all possible arrays.

Example 1:
Input: mat = [[1,3,11],[2,4,6]], k = 5
Output: 7
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.

Example 2:
Input: mat = [[1,3,11],[2,4,6]], k = 9
Output: 17

Example 3:
Input: mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
Output: 9
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]. Where the 7th sum is 9.

Example 4:
Input: mat = [[1,1,10],[2,2,9]], k = 7
Output: 12

Constraints:
m == mat.length
n == mat.length[i]
1 <= m, n <= 40
1 <= k <= min(200, n ^ m)
1 <= mat[i][j] <= 5000
mat[i] is a non decreasing array.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int> row = mat[0];
        for (int i = 1; i < mat.size(); ++i) {
            vector<int> nr;
            for (int j = 0; j < mat[i].size(); ++j) {
                for (auto n : row) {
                    nr.push_back(mat[i][j] + n);
                }
            }
            sort(nr.begin(), nr.end());
            row.resize(min(k, int(nr.size())));
            for (int x = 0; x < min(k, int(nr.size())); ++x) {
                row[x] = nr[x];
            }
        }
        return row[k - 1];
    }
};
