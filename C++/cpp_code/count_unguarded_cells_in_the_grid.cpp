/*
https://leetcode.com/problems/count-unguarded-cells-in-the-grid/description/
2257. Count Unguarded Cells in the Grid

You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards
and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth
wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position
unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.



Example 1:


Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.
Example 2:


Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.


Constraints:

1 <= m, n <= 105
2 <= m * n <= 105
1 <= guards.length, walls.length <= 5 * 104
2 <= guards.length + walls.length <= m * n
guards[i].length == walls[j].length == 2
0 <= rowi, rowj < m
0 <= coli, colj < n
All the positions in guards and walls are unique.
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
#include <set>
using namespace std;

class Solution {
private:
    vector<int> diff_ = {0, 1, 0, -1, 0};
    bool is_valid(int m, int n, int r, int c) {
        return r < m && r >= 0 && c < n && c >= 0;
    }

public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> guarded(m, vector<int>(n, 0));
        for (vector<int>& wall : walls) {
            guarded[wall[0]][wall[1]] = 1;
        }
        for (vector<int>& guard : guards) {
            guarded[guard[0]][guard[1]] = 2;
        }

        for (vector<int>& guard : guards) {
            int cur_r = guard[0];
            int cur_c = guard[1];
            for (int i = 0; i < 4; i++) {
                int diff_r = diff_[i];
                int diff_c = diff_[i + 1];

                int next_r = cur_r + diff_r;
                int next_c = cur_c + diff_c;
                while (is_valid(m, n, next_r, next_c)) {
                    if (guarded[next_r][next_c] == 2 || guarded[next_r][next_c] == 1) {
                        break;
                    }

                    guarded[next_r][next_c] = 3;
                    next_r += diff_r;
                    next_c += diff_c;
                }
            }
        }

        int rst = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (guarded[i][j] == 0) {
                    rst += 1;
                }
            }
        }
        return rst;
    }
};
