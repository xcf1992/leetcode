/*
1293. Shortest Path in a Grid with Obstacles Elimination

You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down,
left, or right from and to an empty cell in one step.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1)
given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.



Example 1:


Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
Output: 6
Explanation:
The shortest path without eliminating any obstacle is 10.
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) ->
(2,2) -> (3,2) -> (4,2). Example 2:


Input: grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
Output: -1
Explanation: We need to eliminate at least two obstacles to find such a walk.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 40
1 <= k <= m * n
grid[i][j] is either 0 or 1.
grid[0][0] == grid[m - 1][n - 1] == 0
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
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        queue<vector<int>> bfs;
        bfs.push({0, 0, 0}); // row col eliminated_cnt
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k + 1, false)));
        visited[0][0][0] = true;

        vector<int> diff({0, 1, 0, -1, 0});
        int result = 0;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; ++i) {
                int row = bfs.front()[0];
                int col = bfs.front()[1];
                int cnt = bfs.front()[2];
                bfs.pop();

                if (row == m - 1 && col == n - 1) {
                    return result;
                }

                for (int j = 1; j < diff.size(); ++j) {
                    int next_r = row + diff[j];
                    int next_c = col + diff[j - 1];
                    int next_cnt = cnt;
                    if (next_r >= 0 && next_c >= 0 && next_r < m && next_c < n) {
                        if (grid[next_r][next_c] == 1) {
                            next_cnt += 1;
                        }

                        if (next_cnt <= k and !visited[next_r][next_c][next_cnt]) {
                            visited[next_r][next_c][next_cnt] = true;
                            bfs.push({next_r, next_c, next_cnt});
                        }
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};