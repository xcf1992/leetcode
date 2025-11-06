/*
1738. Find Kth Largest XOR Coordinate Value
https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/

You are given a 2D matrix of size m x n, consisting of non-negative integers.
You are also given an integer k.

The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j]
where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
Find the kth largest value (1-indexed) of all the coordinates of matrix.

Example 1:
Input: matrix = [[5,2],[1,6]], k = 1
Output: 7
Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
Example 2:
Input: matrix = [[5,2],[1,6]], k = 2
Output: 5
Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd largest value.
Example 3:
Input: matrix = [[5,2],[1,6]], k = 3
Output: 4
Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd largest value.
Example 4:
Input: matrix = [[5,2],[1,6]], k = 4
Output: 0
Explanation: The value of coordinate (1,1) is 5 XOR 2 XOR 1 XOR 6 = 0, which is the 4th largest value.

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
0 <= matrix[i][j] <= 106
1 <= k <= m * n
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int i, j, n = matrix.size(), m = matrix[0].size();
        priority_queue<int, vector<int>, greater<int>> pq;

        // Step 1
        for (i = 0; i < n; i++) {
            for (j = 1; j < m; j++) {
                matrix[i][j] = matrix[i][j - 1] ^ matrix[i][j];
            }
        }

        // Step 2
        for (i = 0; i < m; i++) {
            for (j = 1; j < n; j++) {
                matrix[j][i] = matrix[j - 1][i] ^ matrix[j][i];
            }
        }

        // Step 3
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (pq.size() < k)
                    pq.push(matrix[i][j]);
                else {
                    if (matrix[i][j] > pq.top()) {
                        pq.pop();
                        pq.push(matrix[i][j]);
                    }
                }
            }
        }

        return pq.top();
    }
};