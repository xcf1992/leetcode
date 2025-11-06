/*
1263. Minimum Moves to Move a Box to Their Target Location
https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/

Storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.

The game is represented by a grid of size m x n,
where each element is a wall, floor, or a box.

Your task is move the box 'B' to the target position 'T' under the following rules:
Player is represented by character 'S' and can move up, down, left, right in the grid if it is a floor (empy cell).
Floor is represented by character '.' that means free cell to walk.
Wall is represented by character '#' that means obstacle  (impossible to walk there).
There is only one box 'B' and one target cell 'T' in the grid.
The box can be moved to an adjacent free cell by standing next to the box
and then moving in the direction of the box. This is a push.
The player cannot walk through the box.

Return the minimum number of pushes to move the box to the target.
If there is no way to reach the target, return -1.

Example 1:
Input: grid = [["#","#","#","#","#","#"],
               ["#","T","#","#","#","#"],
               ["#",".",".","B",".","#"],
               ["#",".","#","#",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: 3
Explanation: We return only the number of times the box is pushed.

Example 2:
Input: grid = [["#","#","#","#","#","#"],
               ["#","T","#","#","#","#"],
               ["#",".",".","B",".","#"],
               ["#","#","#","#",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: -1

Example 3:
Input: grid = [["#","#","#","#","#","#"],
               ["#","T",".",".","#","#"],
               ["#",".","#","B",".","#"],
               ["#",".",".",".",".","#"],
               ["#",".",".",".","S","#"],
               ["#","#","#","#","#","#"]]
Output: 5
Explanation:  push the box down, left, left, up and up.

Example 4:
Input: grid = [["#","#","#","#","#","#","#"],
               ["#","S","#",".","B","T","#"],
               ["#","#","#","#","#","#","#"]]
Output: -1

Constraints:
m == grid.length
n == grid[i].length
1 <= m <= 20
1 <= n <= 20
grid contains only characters '.', '#',  'S' , 'T', or 'B'.
There is only one character 'S', 'B' and 'T' in the grid.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    bool isValid(vector<vector<char>>& grid, int row, int col) {
        if (row < 0 or col < 0 or row >= m or col >= n) {
            return false;
        }
        return grid[row][col] != '#';
    }

    bool canWalk(vector<vector<char>>& grid, int sr, int sc, int er,
                 int ec) {  // check if a man can walk from (sr, sc) to (er, ec)
        vector<vector<bool>> memo(m, vector<bool>(n, false));
        return dfs(grid, sr, sc, er, ec, memo);
    }

    bool dfs(vector<vector<char>>& grid, int sr, int sc, int er, int ec, vector<vector<bool>>& memo) {
        if (!isValid(grid, sr, sc)) {
            return false;
        }
        if (sr == er and sc == ec) {
            return true;
        }
        if (memo[sr][sc]) {
            return false;
        }

        memo[sr][sc] = true;
        for (int i = 1; i < diff.size(); ++i) {
            int nr = sr + diff[i];
            int nc = sc + diff[i - 1];
            if (dfs(grid, nr, nc, er, ec, memo)) {
                return true;
            }
        }
        return false;
    }

public:
    int minPushBox(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int box = -1;
        int target = -1;
        int player = -1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'B') {
                    box = i * n + j;
                } else if (grid[i][j] == 'T') {
                    target = i * n + j;
                } else if (grid[i][j] == 'S') {
                    player = i * n + j;
                }
            }
        }

        set<pair<int, int>> visited;  // player-box
        queue<pair<int, int>> bfs;
        vector<vector<int>> walk(m, vector<int>(n, 0));
        visited.insert({player, box});
        bfs.push({player, box});
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int player = bfs.front().first;
                int curBox = bfs.front().second;
                bfs.pop();

                if (curBox == target) {
                    return result;
                }

                grid[curBox / n][curBox % n] = '#';  // mark box as obstacle
                for (int k = 1; k < diff.size(); ++k) {
                    int nexBoxR = curBox / n + diff[k];
                    int nexBoxC = curBox % n + diff[k - 1];
                    int nexPlayerR = curBox / n - diff[k];
                    int nexPlayerC = curBox % n - diff[k - 1];
                    if (isValid(grid, nexBoxR, nexBoxC) and isValid(grid, nexPlayerR, nexPlayerC) and
                        visited.find({nexPlayerR * n + nexPlayerC, nexBoxR * n + nexBoxC}) == visited.end() and
                        canWalk(grid, player / n, player % n, nexPlayerR, nexPlayerC)) {
                        visited.insert({nexPlayerR * n + nexPlayerC, nexBoxR * n + nexBoxC});
                        bfs.push({nexPlayerR * n + nexPlayerC, nexBoxR * n + nexBoxC});
                    }
                }
                grid[curBox / n][curBox % n] = '.';
            }
            result += 1;
        }
        return -1;
    }
};
