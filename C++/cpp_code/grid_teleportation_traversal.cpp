/*
https://leetcode.com/problems/grid-teleportation-traversal/description/
3552. Grid Teleportation Traversal

You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j]
represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:

'.' representing an empty cell.
'#' representing an obstacle.
An uppercase letter ('A'-'Z') representing a teleportation portal.
You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from
the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds
and is not an obstacle.

If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly
teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each
portal letter can be used at most once during your journey.

Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the
destination, return -1.



Example 1:

Input: matrix = ["A..",".A.","..."]

Output: 2

Explanation:



Before the first move, teleport from (0, 0) to (1, 1).
In the first move, move from (1, 1) to (1, 2).
In the second move, move from (1, 2) to (2, 2).
Example 2:

Input: matrix = [".#...",".#.#.",".#.#.","...#."]

Output: 13

Explanation:





Constraints:

1 <= m == matrix.length <= 103
1 <= n == matrix[i].length <= 103
matrix[i][j] is either '#', '.', or an uppercase English letter.
matrix[0][0] is not an obstacle.
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
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<pair<int, int>>> teleports(26, vector<pair<int, int>>());
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
                    teleports[matrix[i][j] - 'A'].push_back({i, j});
                }
            }
        }

        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        if (matrix[0][0] >= 'A' && matrix[0][0] <= 'Z') {
            for (pair<int, int>& ports : teleports[matrix[0][0] - 'A']) {
                bfs.push(ports);
                visited[ports.first][ports.second] = true;
                matrix[ports.first][ports.second] = '.';
            }
        } else {
            bfs.push({0, 0});
            visited[0][0] = true;
        }
        int rst = 0;

        vector<int> diff({0, 1, 0, -1, 0});
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; i++) {
                int cur_r = bfs.front().first;
                int cur_c = bfs.front().second;
                bfs.pop();

                if (cur_r == m - 1 && cur_c == n - 1) {
                    return rst;
                }

                for (int j = 1; j < diff.size(); j++) {
                    int next_r = cur_r + diff[j - 1];
                    int next_c = cur_c + diff[j];

                    if (next_r < 0 || next_r >= m || next_c < 0 || next_c >= n) {
                        continue;
                    }

                    if (visited[next_r][next_c] || matrix[next_r][next_c] == '#') {
                        continue;
                    }

                    if (matrix[next_r][next_c] == '.') {
                        visited[next_r][next_c] = true;
                        bfs.push({next_r, next_c});
                    } else {
                        for (pair<int, int>& ports : teleports[matrix[next_r][next_c] - 'A']) {
                            bfs.push(ports);
                            visited[ports.first][ports.second] = true;
                            matrix[ports.first][ports.second] = '.';
                        }
                    }
                }
            }
            rst += 1;
        }
        return -1;
    }
};