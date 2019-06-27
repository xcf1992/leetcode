/*
778. Swim in Rising Water
On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

Example 1:

Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:

Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
Note:

2 <= N <= 50.
grid[i][j] is a permutation of [0, ..., N*N - 1].
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
Imagine the grid as 
So what the problem ask is to find a
*/
class Solution {
private:
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    void dfs(vector<vector<int>> &grid, int row, int col, int elevation, vector<vector<int>> &dp) {
        if (row < 0 or col < 0 or row >= n or col >= n) {
            return;
        }
        if (elevation >= dp[row][col]) {
            return;
        }

        elevation = max(elevation, grid[row][col]);
        dp[row][col] = elevation;
        for (int i = 1; i < diff.size(); ++i) {
            dfs(grid, row + diff[i], col + diff[i - 1], elevation, dp);
        }
    }
public:
    int swimInWater(vector<vector<int>> &grid) {
        n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        dfs(grid, 0, 0, 0, dp);
        return dp[n - 1][n - 1];
    }
};
