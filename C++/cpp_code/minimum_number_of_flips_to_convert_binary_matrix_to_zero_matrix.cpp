/*
1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/

Given a m x n binary matrix mat.
In one step, you can choose one cell and flip it and all the four neighbours of it
if they exist (Flip is changing 1 to 0 and 0 to 1).
A pair of cells are called neighboors if they share one edge.

Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
Binary matrix is a matrix with all cells equal to 0 or 1 only.
Zero matrix is a matrix with all cells equal to 0.

Example 1:
0 0   1 0   0 1   0 0
   -->   -->   -->
0 1   1 0   1 1   0 0
Input: mat = [[0,0],[0,1]]
Output: 3
Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.

Example 2:
Input: mat = [[0]]
Output: 0
Explanation: Given matrix is a zero matrix. We don't need to change it.

Example 3:
Input: mat = [[1,1,1],[1,0,1],[0,0,0]]
Output: 6

Example 4:
Input: mat = [[1,0,0],[1,0,0]]
Output: -1
Explanation: Given matrix can't be a zero matrix

Constraints:
m == mat.length
n == mat[0].length
1 <= m <= 3
1 <= n <= 3
mat[i][j] is 0 or 1.
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
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    int createBitVector(vector<vector<int>>& mat) {
        int bitVec = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                bitVec <<= 1;
                bitVec |= mat[i][j];
            }
        }
        return bitVec;
    }

    int flip(int i, int j, int bitVec) {
        int pos = m * n - 1 - (i * n + j);
        bitVec ^= (1 << pos);
        for (int k = 1; k < diff.size(); ++k) {
            int ni = i + diff[k];
            int nj = j + diff[k - 1];
            if (ni >= 0 and ni < m and nj >= 0 and nj < n) {
                pos = m * n - 1 - (ni * n + nj);
                bitVec ^= (1 << pos);
            }
        }
        return bitVec;
    }

public:
    int minFlips(vector<vector<int>>& mat) {
        m = mat.size();
        n = mat[0].size();
        int bitVec = createBitVector(mat);
        if (bitVec == 0) {
            return 0;
        }

        queue<int> bfs;
        unordered_set<int> visited;
        int result = 0;
        bfs.push(bitVec);
        visited.insert(bitVec);
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int curBit = bfs.front();
                bfs.pop();
                if (curBit == 0) {
                    return result;
                }

                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        int nextBit = flip(i, j, curBit);
                        if (visited.find(nextBit) == visited.end()) {
                            bfs.push(nextBit);
                            visited.insert(nextBit);
                        }
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};
