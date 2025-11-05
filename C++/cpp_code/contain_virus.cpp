/*
749. Contain Virus
A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

The world is modeled as a 2-D array of cells, where 0 represents uninfected cells,
and 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall.
Resources are limited. Each day, you can install walls around only one region --
the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night.
There will never be a tie.

Can you save the day? If so, what is the number of walls required? If not, and the world becomes fully infected, return the number of walls used.

Example 1:
Input: grid =
[[0,1,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,0]]
Output: 10
Explanation:
There are 2 contaminated regions.
On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:

[[0,1,0,0,0,0,1,1],
 [0,1,0,0,0,0,1,1],
 [0,0,0,0,0,0,1,1],
 [0,0,0,0,0,0,0,1]]

On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
Example 2:
Input: grid =
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output: 4
Explanation: Even though there is only one cell saved, there are 4 walls built.
Notice that walls are only built on the shared boundary of two different cells.
Example 3:
Input: grid =
[[1,1,1,0,0,0,0,0,0],
 [1,0,1,0,1,1,1,1,1],
 [1,1,1,0,0,0,0,0,0]]
Output: 13
Explanation: The region on the left only builds two new walls.
Note:
The number of rows and columns of grid will each be in the range [1, 50].
Each grid[i][j] will be either 0 or 1.
Throughout the described process, there is always a contiguous viral region that will infect strictly more uncontaminated squares in the next round.
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
#include <stdio.h>
#include <map>
using namespace std;

/*
The solution simply models the process.

Build walls = set those connected virus inactive, i.e. set as -1;
Affected area != walls; For example, one 0 surrounded by all 1s have area = 1, but walls = 4.
*/
class Solution {
private:
    int m = 0;
    int n = 0;

    int process(vector<vector<int> > &grid) {
        int count = 0;
        int result = 0;
        int color = -1;
        int row = -1;
        int col = -1;
        vector<vector<int> > visited(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 and visited[i][j]
                ==
                0
                )
                {
                    int walls = 0;
                    int area = dfs(grid, visited, i, j, color, walls);
                    if (area > count) {
                        result = walls;
                        count = area;
                        row = i;
                        col = j;
                    }
                    color -= 1;
                }
            }
        }

        buildWall(grid, row, col);

        visited = vector<vector<int> >(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 and visited[i][j]
                ==
                0
                )
                {
                    spread(grid, visited, i, j);
                }
            }
        }
        return result;
    }

    int dfs(vector<vector<int> > &grid, vector<vector<int> > &visited, int row, int col, int color, int &walls) {
        if (row < 0 or col<0 or row >= m or col >= n or visited[row][col] == 1 or grid[row][col] == -1
        )
        {
            return 0;
        }

        int affected_area = 0;
        if (grid[row][col] == 0) {
            walls += 1;
            if (visited[row][col] == color) {
                return 0;
            }
            visited[row][col] = color;
            return 1;
        }
        visited[row][col] = 1;

        affected_area += dfs(grid, visited, row - 1, col, color, walls);
        affected_area += dfs(grid, visited, row + 1, col, color, walls);
        affected_area += dfs(grid, visited, row, col - 1, color, walls);
        affected_area += dfs(grid, visited, row, col + 1, color, walls);
        return affected_area;
    }

    void buildWall(vector<vector<int> > &grid, int row, int col) {
        if (row < 0 or col<0 or row >= m or col >= n or grid[row][col] != 1
        )
        {
            return;
        }
        grid[row][col] = -1;

        buildWall(grid, row + 1, col);
        buildWall(grid, row - 1, col);
        buildWall(grid, row, col + 1);
        buildWall(grid, row, col - 1);
    }

    void spread(vector<vector<int> > &grid, vector<vector<int> > &visited, int row, int col) {
        if (row < 0 or col<0 or row >= m or col >= n or visited[row][col]
        )
        {
            return;
        }

        if (grid[row][col] == 0) {
            grid[row][col] = 1;
            visited[row][col] = 1;
        } else if (grid[row][col] == 1) {
            visited[row][col] = 1;
            spread(grid, visited, row, col - 1);
            spread(grid, visited, row, col + 1);
            spread(grid, visited, row - 1, col);
            spread(grid, visited, row + 1, col);
        }
    }

public:
    int containVirus(vector<vector<int> > &grid) {
        int m = grid.size();
        int n = grid[0].size();

        int result = 0;
        while (true) {
            int walls = process(grid);
            if (walls == 0) {
                break;
            }
            result += walls;
        }
        return result;
    }
};