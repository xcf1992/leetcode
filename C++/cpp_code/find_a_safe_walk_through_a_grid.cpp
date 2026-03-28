/*
https://leetcode.com/problems/find-a-safe-walk-through-a-grid/description/
3286. Find a Safe Walk Through a Grid

You are given an m x n binary matrix grid and an integer health.

You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.



Example 1:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.


Example 2:

Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3

Output: false

Explanation:

A minimum of 4 health points is needed to reach the final cell safely.


Example 3:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.



Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final
cell.



Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
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
    vector<int> diff_ = {0, 1, 0, -1, 0};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> max_health(m, vector<int>(n, 0));
        max_health[0][0] = health - grid[0][0];
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;
        pq.push({max_health[0][0], 0});
        while (!pq.empty()) {
            int cur_r = pq.top().second / n;
            int cur_c = pq.top().second % n;
            int cur_h = pq.top().first;
            pq.pop();

            if (cur_h < max_health[cur_r][cur_c]) {
                continue;
            }

            if (cur_r == m - 1 && cur_c == n - 1) {
                return true;
            }

            for (int i = 0; i < 4; i++) {
                int next_r = cur_r + diff_[i];
                int next_c = cur_c + diff_[i + 1];
                if (next_r < 0 || next_r >= m || next_c < 0 || next_c >= n) {
                    continue;
                }

                int next_h = cur_h - grid[next_r][next_c];
                if (next_h <= 0 || next_h <= max_health[next_r][next_c]) {
                    continue;
                }

                max_health[next_r][next_c] = next_h;
                pq.push({next_h, next_r * n + next_c});
            }
        }
        return false;
    }
};