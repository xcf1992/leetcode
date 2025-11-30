/*
1210. Minimum Moves to Reach Target with Rotations
https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/

In an n*n grid,
there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1).
The grid has empty cells represented by zeros and blocked cells represented by ones.
The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).

In one move the snake can:
Move one cell to the right if there are no blocked cells there.
This move keeps the horizontal/vertical position of the snake as it is.

Move down one cell if there are no blocked cells there.
This move keeps the horizontal/vertical position of the snake as it is.

Rotate clockwise if it's in a horizontal position and the two cells under it are both empty.
In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).

Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty.
In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).

Return the minimum number of moves to reach the target.
If there is no way to reach the target, return -1.

Example 1:
Input: grid = [[0,0,0,0,0,1],
               [1,1,0,0,1,0],
               [0,0,0,0,1,1],
               [0,0,1,0,1,0],
               [0,1,1,0,0,0],
               [0,1,1,0,0,0]]
Output: 11
Explanation:
One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right,
down].

Example 2:
Input: grid = [[0,0,1,1,1,1],
               [0,0,0,0,1,1],
               [1,1,0,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,0]]
Output: 9

Constraints:
2 <= n <= 100
0 <= grid[i][j] <= 1
It is guaranteed that the snake starts at empty cells.
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
#include "extra_data_types.hpp"
using namespace std;
/*
This type of problems is not hard,
but it could be trickly to get the code right.
I created three helper functions to make it a bit easier.

Use a queue to store the tail coordinates and orientation.
For every element in the queue, check the visited flag and move up, down or rotate, if possible.
Here, I am using second and third bit (2 and 4) to track the state directly in the grid.
*/
class Solution {
private:
    int n = 0;

    bool canMoveDown(vector<vector<int>>& grid, int row, int col, bool isVertical) {
        if (isVertical) {
            return row < n - 2 and (grid[row + 2][col] & 1) == 0;
        }
        return row < n - 1 and (grid[row + 1][col] & 1) == 0 and (grid[row + 1][col + 1] & 1) == 0;
    }

    bool canMoveRight(vector<vector<int>>& grid, int row, int col, bool isVertical) {
        if (!isVertical) {
            return col < n - 2 and (grid[row][col + 2] & 1) == 0;
        }
        return col < n - 1 and (grid[row][col + 1] & 1) == 0 and (grid[row + 1][col + 1] & 1) == 0;
    }

    bool canRotate(vector<vector<int>>& grid, int row, int col) {
        return row < n - 1 and col < n - 1 and (grid[row][col + 1] & 1) == 0 and (grid[row + 1][col] & 1) == 0 and
               (grid[row + 1][col + 1] & 1) == 0;
    }

public:
    int minimumMoves(vector<vector<int>>& grid) {
        n = grid.size();
        queue<vector<int>> bfs;
        bfs.push({0, 0, 0});  // tail pos and isVertical
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int row = bfs.front()[0];
                int col = bfs.front()[1];
                bool isVertical = bfs.front()[2] == 1;
                bfs.pop();

                if (row == n - 1 and col == n - 2) {
                    return result;
                }

                if ((grid[row][col] & (isVertical ? 2 : 4)) == 0) {
                    grid[row][col] |= (isVertical ? 2 : 4);
                    if (canMoveDown(grid, row, col, isVertical)) {
                        bfs.push({row + 1, col, isVertical});
                    }
                    if (canMoveRight(grid, row, col, isVertical)) {
                        bfs.push({row, col + 1, isVertical});
                    }
                    if (canRotate(grid, row, col)) {
                        bfs.push({row, col, isVertical ? 0 : 1});
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};
