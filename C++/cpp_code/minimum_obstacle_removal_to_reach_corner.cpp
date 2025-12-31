/*
https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/
2290. Minimum Obstacle Removal to Reach Corner

You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:

0 represents an empty cell,
1 represents an obstacle that may be removed.
You can move up, down, left, or right from and to an empty cell.

Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right
corner (m - 1, n - 1).



Example 1:


Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.
Example 2:


Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 105
2 <= m * n <= 105
grid[i][j] is either 0 or 1.
grid[0][0] == grid[m - 1][n - 1] == 0
*/
#include <iostream>
#include <sstream>
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

struct myComp {
    bool operator() (const vector<int>& a, const vector<int>& b) {
        return a[0] > b[0];
    }
};

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> diff = {0, 1, 0, -1, 0};

        vector<vector<int>> obstacles(m, vector<int>(n, INT_MAX));
        obstacles[0][0] = 0;

        priority_queue<vector<int>, vector<vector<int>>, myComp> pq;
        pq.push({0, 0, 0});
        while (!pq.empty()) {
            int cur_row = pq.top()[1];
            int cur_col = pq.top()[2];
            int cur_obstacle = pq.top()[0];
            pq.pop();

            if (cur_row == m - 1 && cur_col == n - 1) {
                return cur_obstacle;
            }

            for (int i = 0; i < 4; i++) {
                int next_row = cur_row + diff[i];
                int next_col = cur_col + diff[i + 1];

                if (next_row < 0 || next_row >= m || next_col < 0 || next_col >= n) {
                    continue;
                }

                int next_obstacle = cur_obstacle + grid[next_row][next_col];
                if (next_obstacle < obstacles[next_row][next_col]) {
                    obstacles[next_row][next_col] = next_obstacle;
                    pq.push({next_obstacle, next_row, next_col});
                }
            }
        }

        return obstacles[m - 1][n - 1];
    }
};
