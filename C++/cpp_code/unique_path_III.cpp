/*
980. Unique Paths III

On a 2-dimensional grid, there are 4 types of squares:
1 represents the starting square.
There is exactly one starting square.

2 represents the ending square.
There is exactly one ending square.

0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.

Return the number of 4-directional walks from the starting square to the ending square,
that walk over every non-obstacle square exactly once.

Example 1:
Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:
Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:
Input: [[0,1],[2,0]]
Output: 0
Explanation:
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Note:
1 <= grid.length * grid[0].length <= 20
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
    int M = 0;
    int N = 0;
    int obs = 0;
    vector<int> diff = {0, -1, 0, 1, 0};

    void traverse(vector<vector<int>>& grid, int row, int col, int& result, int path, vector<vector<bool>>& visited) {
        if (row < 0 or col < 0 or row >= M or col >= N or visited[row][col] or grid[row][col] == -1) {
            return;
        }

        if (grid[row][col] == 2) {
            if (path + obs + 1 == M * N) {
                result += 1;
            }
            return;
        }

        visited[row][col] = true;
        path += 1;
        for (int i = 1; i < diff.size(); ++i) {
            traverse(grid, row + diff[i], col + diff[i - 1], result, path, visited);
        }
        path -= 1;
        visited[row][col] = false;
    }

public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();
        int row = 0;
        int col = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == -1) {
                    obs += 1;
                }
                if (grid[i][j] == 1) {
                    row = i;
                    col = j;
                }
            }
        }

        int result = 0;
        int path = 0;
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        traverse(grid, row, col, result, path, visited);
        return result;
    }
};