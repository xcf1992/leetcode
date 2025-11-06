/*
https://leetcode.com/problems/find-the-safest-path-in-a-grid/
2812. Find the Safest Path in a Grid
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

A cell containing a thief if grid[r][c] = 1
An empty cell if grid[r][c] = 0
You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells
containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any
thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the
absolute value of val.



Example 1:


Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
Output: 0
Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
Example 2:


Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0
- 2 | = 2. It can be shown that there are no other paths with a higher safeness factor. Example 3:


Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3
- 2 | = 2.
- The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0
- 2 | = 2. It can be shown that there are no other paths with a higher safeness factor.


Constraints:

1 <= grid.length == n <= 400
grid[i].length == n
grid[i][j] is either 0 or 1.
There is at least one thief in the grid.
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
#include <set>
#include <map>
#include <numeric>
using namespace std;

struct comp {
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    }
};

class Solution {
private:
    vector<int> dir = {0, 1, 0, -1, 0};

    void calc_safe_factor(const vector<vector<int>>& grid, vector<vector<int>>& safe_factor) {
        int n = grid.size();
        queue<pair<int, int>> bfs;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    bfs.push(pair<int, int>(i, j));
                    safe_factor[i][j] = 0;
                }
            }
        }

        while (!bfs.empty()) {
            int row = bfs.front().first;
            int col = bfs.front().second;
            bfs.pop();

            for (int i = 0; i < 4; ++i) {
                int nxt_row = row + dir[i];
                int nxt_col = col + dir[i + 1];
                if (nxt_row < 0 || nxt_row >= n || nxt_col < 0 || nxt_col >= n) {
                    continue;
                }
                if (safe_factor[nxt_row][nxt_col] > safe_factor[row][col] + 1) {
                    safe_factor[nxt_row][nxt_col] = safe_factor[row][col] + 1;
                    bfs.push(pair<int, int>(nxt_row, nxt_col));
                }
            }
        }
    }

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        vector<vector<int>> safe_factor(n, vector<int>(n, INT_MAX));
        calc_safe_factor(grid, safe_factor);

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        priority_queue<vector<int>, vector<vector<int>>, comp> pq;
        pq.push({0, 0, safe_factor[0][0]});
        visited[0][0] = true;
        while (!pq.empty()) {
            int cur_r = pq.top()[0];
            int cur_c = pq.top()[1];
            int cur_safe_factor = pq.top()[2];
            pq.pop();

            if (cur_r == n - 1 && cur_c == n - 1) {
                return cur_safe_factor;
            }

            for (int i = 0; i < 4; ++i) {
                int nxt_r = cur_r + dir[i];
                int nxt_c = cur_c + dir[i + 1];
                if (nxt_r < 0 || nxt_r >= n || nxt_c < 0 || nxt_c >= n || visited[nxt_r][nxt_c]) {
                    continue;
                }

                pq.push({nxt_r, nxt_c, min(cur_safe_factor, safe_factor[nxt_r][nxt_c])});
                visited[nxt_r][nxt_c] = true;
            }
        }
        return -1;
    }
};