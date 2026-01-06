/*
https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/description/
3568. Minimum Moves to Clean the Classroom

You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the
room. Each cell in the grid is one of the following:

'S': Starting position of the student
'L': Litter that must be collected (once collected, the cell becomes empty)
'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be
used multiple times) 'X': Obstacle the student cannot pass through
'.': Empty space
You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this
energy from the starting position 'S'.

Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student
can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.

Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.



Example 1:

Input: classroom = ["S.", "XL"], energy = 2

Output: 2

Explanation:

The student starts at cell (0, 0) with 2 units of energy.
Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
The student collects all the litter using 2 moves. Thus, the output is 2.
Example 2:

Input: classroom = ["LS", "RL"], energy = 4

Output: 3

Explanation:

The student starts at cell (0, 1) with 4 units of energy.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of energy used and 3 units remaining.
Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to 4.
Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
The student collects all the litter using 3 moves. Thus, the output is 3.
Example 3:

Input: classroom = ["L.S", "RXL"], energy = 3

Output: -1

Explanation:

No valid path collects all 'L'.



Constraints:

1 <= m == classroom.length <= 20
1 <= n == classroom[i].length <= 20
classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
1 <= energy <= 50
There is exactly one 'S' in the grid.
There are at most 10 'L' cells in the grid.
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

/*
Hint 1
Use BFS with states (x, y, mask, e, steps), initializing with (sx, sy, 0, energy, 0), and for each move update e (–1 per
step), update mask on 'L', reset e=energy on 'R', and return steps when mask == fullMask.

Hint 2 Maintain a 3D array
bestEnergy[x][y][mask] storing the maximum e seen for each (x,y,mask) and skip any new state with e <=
bestEnergy[x][y][mask] to prune.
 */
class Solution {
private:
    vector<int> diff = {0, 1, 0, -1, 0};

public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        int src_row = -1;
        int src_col = -1;
        int trash_cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    src_row = i;
                    src_col = j;
                    continue;
                }
                if (classroom[i][j] == 'L') {
                    classroom[i][j] = '0' + trash_cnt;
                    trash_cnt += 1;
                }
            }
        }

        if (trash_cnt == 0) {
            return 0;
        }

        int trash_mask = (1 << trash_cnt) - 1;
        vector<vector<vector<int>>> best_energy(m, vector<vector<int>>(n, vector<int>(1024, -1)));
        best_energy[src_row][src_col][0] = energy;

        int cur_step = 0;
        queue<vector<int>> bfs;
        bfs.push({src_row, src_col, 0, energy});  // row, col, mask, energy
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; i++) {
                int cur_row = bfs.front()[0];
                int cur_col = bfs.front()[1];
                int cur_mask = bfs.front()[2];
                int cur_energy = bfs.front()[3];
                bfs.pop();

                if (cur_mask == trash_mask) {
                    return cur_step;
                }

                if (cur_energy == 0) {
                    continue;
                }

                for (int j = 0; j < 4; j++) {
                    int next_row = cur_row + diff[j];
                    int next_col = cur_col + diff[j + 1];
                    if (next_row < 0 || next_col < 0 || next_row >= m || next_col >= n ||
                        classroom[next_row][next_col] == 'X') {
                        continue;
                    }

                    int next_mask = cur_mask;
                    if (isdigit(classroom[next_row][next_col])) {
                        next_mask |= 1 << (classroom[next_row][next_col] - '0');
                    }

                    int next_energy = cur_energy - 1;
                    if (classroom[next_row][next_col] == 'R') {
                        next_energy = energy;
                    }

                    if (best_energy[next_row][next_col][next_mask] < next_energy) {
                        best_energy[next_row][next_col][next_mask] = next_energy;
                        bfs.push({next_row, next_col, next_mask, next_energy});
                    }
                }
            }
            cur_step += 1;
        }
        return -1;
    }
};
