/*
https://leetcode.com/problems/escape-the-spreading-fire/description/?envType=company&envId=snapchat&favoriteSlug=snapchat-all
2258. Escape the Spreading Fire

You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three
values:

0 represents grass,
1 represents fire,
2 represents a wall that you and fire cannot pass through.
You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1,
n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all
adjacent cells that are not walls.

Return the maximum number of minutes that you can stay in your initial position before moving while still safely
reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the
minutes stayed, return 109.

Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely
reaching the safehouse.

A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their
sides are touching).



Example 1:


Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
Output: 3
Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
You will still be able to safely reach the safehouse.
Staying for more than 3 minutes will not allow you to safely reach the safehouse.
Example 2:


Input: grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]
Output: -1
Explanation: The figure above shows the scenario where you immediately move towards the safehouse.
Fire will spread to any cell you move towards and it is impossible to safely reach the safehouse.
Thus, -1 is returned.
Example 3:


Input: grid = [[0,0,0],[2,2,0],[1,2,0]]
Output: 1000000000
Explanation: The figure above shows the initial grid.
Notice that the fire is contained by walls and you will always be able to safely reach the safehouse.
Thus, 109 is returned.


Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 300
4 <= m * n <= 2 * 104
grid[i][j] is either 0, 1, or 2.
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
#include <map>
using namespace std;

class Solution {
private:
    vector<int> diff = {0, 1, 0, -1, 0};

    bool can_reach_after_wait(int cur_time, vector<vector<int>>& fired_at, int cur_r, int cur_c, vector<vector<int>>& visited, int mark) {
        int m = fired_at.size();
        int n = fired_at[0].size();
        if (cur_r == m - 1 && cur_c == n - 1) {
            return true;
        }

        visited[cur_r][cur_c] = mark;
        for (int i = 0; i < 4; i++) {
            int next_r = cur_r + diff[i];
            int next_c = cur_c + diff[i + 1];
            if (next_r >= m || next_c >= n || next_r < 0 || next_c < 0 || visited[next_r][next_c] == mark) {
                continue;
            }

            if (next_r == m - 1 && next_c == n - 1 && fired_at[next_r][next_c] > cur_time) {
                return true;
            }

            if (fired_at[next_r][next_c] > cur_time + 1) {
                if (can_reach_after_wait(cur_time + 1, fired_at, next_r, next_c, visited, mark)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool can_reach_anyway(vector<vector<int>>& fired_at, int cur_r, int cur_c, vector<vector<int>>& visited, int mark) {
        int m = fired_at.size();
        int n = fired_at[0].size();
        if (cur_r == m - 1 && cur_c == n - 1) {
            return true;
        }

        visited[cur_r][cur_c] = mark;
        for (int i = 0; i < 4; i++) {
            int next_r = cur_r + diff[i];
            int next_c = cur_c + diff[i + 1];

            if (next_r >= m || next_c >= n || next_r < 0 || next_c < 0 || visited[next_r][next_c] == mark) {
                continue;
            }

            if (fired_at[next_r][next_c] != INT_MAX) {
                continue;
            }

            if (can_reach_anyway(fired_at, next_r, next_c, visited, mark)) {
                return true;
            }
        }
        return false;
    }
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> fired_at(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> bfs;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fired_at[i][j] = 0;
                    bfs.push({i, j});
                } else if (grid[i][j] == 2) {
                    fired_at[i][j] = -1;
                }
            }
        }

        // calculate fired_at for each cell
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; i++) {
                int cur_row = bfs.front().first;
                int cur_col = bfs.front().second;
                bfs.pop();

                for (int j = 0; j < 4; j++) {
                    int next_row = cur_row + diff[j];
                    int next_col = cur_col + diff[j + 1];
                    if (next_row >= 0 && next_col >= 0 && next_row < m && next_col < n &&
                        fired_at[next_row][next_col] == INT_MAX) {
                        fired_at[next_row][next_col] = fired_at[cur_row][cur_col] + 1;
                        bfs.push({next_row, next_col});
                    }
                }
            }
        }

        // check if can wait infinite time
        vector<vector<int>> visited(m, vector<int>(n, -1));
        int mark = 0;
        if (fired_at[0][0] == INT_MAX && can_reach_anyway(fired_at, 0, 0, visited, mark)) {
            return 1e9;
        }

        // binary search for the max possible wait time
        int left = 0;
        int right = m * n + 1;
        int rst = 0;
        while (left < right) {
            int mid = left + (right - left) / 2;
            mark += 1;
            if (can_reach_after_wait(mid, fired_at, 0, 0, visited, mark)) {
                rst = mid;
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return rst;
    }
};
