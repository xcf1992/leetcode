/*
https://leetcode.com/problems/minimum-path-cost-in-a-hidden-grid/description/
1810. Minimum Path Cost in a Hidden Grid

This is an interactive problem.

There is a robot in a hidden grid, and you are trying to get it from its starting cell to the target cell in this grid.
The grid is of size m x n, and each cell in the grid is either empty or blocked. It is guaranteed that the starting cell
and the target cell are different, and neither of them is blocked.

Each cell has a cost that you need to pay each time you move to the cell. The starting cell's cost is not applied before
the robot moves.

You want to find the minimum total cost to move the robot to the target cell. However, you do not know the grid's
dimensions, the starting cell, nor the target cell. You are only allowed to ask queries to the GridMaster object.

The GridMaster class has the following functions:

boolean canMove(char direction) Returns true if the robot can move in that direction. Otherwise, it returns false.
int move(char direction) Moves the robot in that direction and returns the cost of moving to that cell. If this move
would move the robot to a blocked cell or off the grid, the move will be ignored, the robot will remain in the same
position, and the function will return -1. boolean isTarget() Returns true if the robot is currently on the target cell.
Otherwise, it returns false. Note that direction in the above functions should be a character from {'U','D','L','R'},
representing the directions up, down, left, and right, respectively.

Return the minimum total cost to get the robot from its initial starting cell to the target cell. If there is no valid
path between the cells, return -1.

Custom testing:

The test input is read as a 2D matrix grid of size m x n and four integers r1, c1, r2, and c2 where:

grid[i][j] == 0 indicates that the cell (i, j) is blocked.
grid[i][j] >= 1 indicates that the cell (i, j) is empty and grid[i][j] is the cost to move to that cell.
(r1, c1) is the starting cell of the robot.
(r2, c2) is the target cell of the robot.
Remember that you will not have this information in your code.



Example 1:

Input: grid = [[2,3],[1,1]], r1 = 0, c1 = 1, r2 = 1, c2 = 0
Output: 2
Explanation: One possible interaction is described below:
The robot is initially standing on cell (0, 1), denoted by the 3.
- master.canMove('U') returns false.
- master.canMove('D') returns true.
- master.canMove('L') returns true.
- master.canMove('R') returns false.
- master.move('L') moves the robot to the cell (0, 0) and returns 2.
- master.isTarget() returns false.
- master.canMove('U') returns false.
- master.canMove('D') returns true.
- master.canMove('L') returns false.
- master.canMove('R') returns true.
- master.move('D') moves the robot to the cell (1, 0) and returns 1.
- master.isTarget() returns true.
- master.move('L') doesn't move the robot and returns -1.
- master.move('R') moves the robot to the cell (1, 1) and returns 1.
We now know that the target is the cell (1, 0), and the minimum total cost to reach it is 2.
Example 2:

Input: grid = [[0,3,1],[3,4,2],[1,2,0]], r1 = 2, c1 = 0, r2 = 0, c2 = 2
Output: 9
Explanation: The minimum cost path is (2,0) -> (2,1) -> (1,1) -> (1,2) -> (0,2).
Example 3:

Input: grid = [[1,0],[0,1]], r1 = 0, c1 = 0, r2 = 1, c2 = 1
Output: -1
Explanation: There is no path from the robot to the target cell.


Constraints:

1 <= n, m <= 100
m == grid.length
n == grid[i].length
0 <= grid[i][j] <= 100
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

/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class GridMaster {
public:
    bool canMove(char direction);
    int move(char direction);
    bool isTarget();
};
/*
That is a very intuitive thought! However, there is a fundamental reason why a single DFS cannot find the minimum cost
in this specific problem: DFS is not designed for shortest paths in weighted graphs.

Here is the breakdown of why the two-step approach is necessary.

1. DFS finds "A" path, not the "Shortest" path
In a grid where every move has a different cost, the first time DFS reaches the target, it might have taken a very
expensive "scenic route."

To find the absolute minimum cost using only DFS, you would have to explore every single possible path to the target to
compare them. In a grid, the number of possible paths grows exponentially, which would lead to a Time Limit Exceeded
(TLE) error.

2. The "Physical" Robot Constraint
Unlike a typical programming problem where you can just "jump" to a coordinate in an array, here you are controlling a
physical entity.

In Dijkstra: We need to jump between the "cheapest" nodes currently known (often on opposite sides of the map). The
robot cannot teleport.

In DFS: The robot moves step-by-step.

If you tried to run Dijkstra directly, you would spend more moves just moving the robot back and forth between the
"frontier" nodes than actually exploring.

The Hybrid Solution
By separating the concerns, we solve both issues:

Phase 1 (DFS): Moves the robot physically to "scan" the environment and build a virtual map. This only visits each cell
once (with backtracking).

Phase 2 (Dijkstra): Runs entirely in memory on the map we just built. It finds the shortest path mathematically without
needing to move the physical robot anymore.
*/
struct myComp {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[0] > b[0];
    }
};

class Solution {
private:
    vector<char> directions_ = {'U', 'R', 'D', 'L'};
    vector<int> diff_ = {-1, 0, 1, 0, -1};
    int dest_row_ = -1;
    int dest_col_ = -1;

    void dfs(int cur_row, int cur_col, GridMaster& master, vector<vector<int>>& costs) {
        if (master.isTarget()) {
            dest_row_ = cur_row;
            dest_col_ = cur_col;
        }

        for (int i = 0; i < 4; i++) {
            char dir = directions_[i];
            int next_row = cur_row + diff_[i];
            int next_col = cur_col + diff_[i + 1];
            if (!master.canMove(dir)) {
                costs[next_row][next_col] = 0;  // blocked
            } else if (costs[next_row][next_col] == -1) {
                int cost = master.move(dir);
                costs[next_row][next_col] = cost;
                dfs(next_row, next_col, master, costs);
                // move and return
                master.move(directions_[(i + 2) % 4]);
            }
        }
    }

    int get_min_cost(int n, int src_row, int src_col, vector<vector<int>>& costs) {
        vector<vector<int>> min_costs(n, vector<int>(n, INT_MAX));
        min_costs[src_row][src_col] = 0;

        priority_queue<vector<int>, vector<vector<int>>, myComp> pq;
        pq.push({0, src_row, src_col});

        while (!pq.empty()) {
            int cur_cost = pq.top()[0];
            int cur_row = pq.top()[1];
            int cur_col = pq.top()[2];
            pq.pop();

            if (cur_cost > min_costs[cur_row][cur_col]) {
                continue;
            }

            if (cur_row == dest_row_ && cur_col == dest_col_) {
                return cur_cost;
            }

            for (int i = 0; i < 4; i++) {
                int next_row = cur_row + diff_[i];
                int next_col = cur_col + diff_[i + 1];
                if (costs[next_row][next_col] == 0) {
                    continue;
                }

                if (cur_cost + costs[next_row][next_col] < min_costs[next_row][next_col]) {
                    min_costs[next_row][next_col] = cur_cost + costs[next_row][next_col];
                    pq.push({min_costs[next_row][next_col], next_row, next_col});
                }
            }
        }
        return -1;
    }

public:
    int findShortestPath(GridMaster& master) {
        int max_size = 512;
        int src_row = max_size / 2;
        int src_col = max_size / 2;
        vector<vector<int>> costs(max_size, vector<int>(max_size, -1));
        costs[src_row][src_col] = 0;

        // dfs to find the cost to each cell of the grid
        dfs(src_row, src_col, master, costs);
        if (dest_row_ == -1 || dest_col_ == -1) {
            // cannot reach dest
            return -1;
        }

        return get_min_cost(max_size, src_row, src_col, costs);
    }
};