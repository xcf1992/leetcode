/*
1091. Shortest Path in Binary Matrix
https://leetcode.com/problems/shortest-path-in-binary-matrix/

In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such
that: Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.
If such a path does not exist, return -1.

Example 1:
Input: [[0,1],[1,0]]
Output: 2

Example 2:
Input: [[0,0,0],[1,1,0],[1,1,0]]
Output: 4

Note:
1 <= grid.length == grid[0].length <= 100
grid[i][j] is 0 or 1
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    int n = 0;

    bool isValid(int r, int c, vector<vector<int>>& grid) {
        return r >= 0 and c >= 0 and r < n and c < n and grid[r][c] == 0;
    }

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        n = grid.size();
        if (grid[0][0] == 1 or grid[n - 1][n - 1] == 1) {
            return -1;
        }

        queue<pair<int, int>> bfs;
        bfs.push({0, 0});
        vector<vector<int>> diff({{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}});
        while (!bfs.empty()) {
            int r = bfs.front().first;
            int c = bfs.front().second;
            bfs.pop();

            if (r == n - 1 and c == n - 1) {
                return grid[r][c] + 1;
            }

            for (int i = 0; i < diff.size(); ++i) {
                int nr = r + diff[i][0];
                int nc = c + diff[i][1];
                if (!isValid(nr, nc, grid)) {
                    continue;
                }
                grid[nr][nc] = grid[r][c] + 1;
                bfs.push({nr, nc});
            }
        }
        return -1;
    }
};