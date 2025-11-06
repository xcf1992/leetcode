/*
542. 01 Matrix
https://leetcode.com/problems/01-matrix/

Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
The distance between two adjacent cells is 1.

Example 1:
Input:
0 0 0
0 1 0
0 0 0
Output:
0 0 0
0 1 0
0 0 0

Example 2:
Input:
0 0 0
0 1 0
1 1 1
Output:
0 0 0
0 1 0
1 2 1

Note:
The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
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
using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> bfs;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    distance[i][j] = 0;
                    bfs.push({i, j});
                }
            }
        }

        int curDis = 0;
        vector<int> diff({0, 1, 0, -1, 0});
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int row = bfs.front().first;
                int col = bfs.front().second;
                bfs.pop();

                for (int i = 1; i < diff.size(); ++i) {
                    int nr = row + diff[i];
                    int nc = col + diff[i - 1];
                    if (nr >= 0 and nc >= 0 and nr < m and nc < n and distance[nr][nc] == INT_MAX) {
                        distance[nr][nc] = curDis + 1;
                        bfs.push({nr, nc});
                    }
                }
            }
            curDis += 1;
        }
        return distance;
    }
};