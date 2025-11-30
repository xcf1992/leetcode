/*
1368. Minimum Cost to Make at Least One Valid Path in a Grid
https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/

Given a m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit
if you are currently in this cell. The sign of grid[i][j] can be:
1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
Notice that there could be some invalid signs on the cells of the grid which points outside the grid.

You will initially start at the upper left cell (0,0).
A valid path in the grid is a path which starts from the upper left cell (0,0)
and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid.
The valid path doesn't have to be the shortest.

You can modify the sign on a cell with cost = 1.
You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.

Example 1:
Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1,
3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3)
change the arrow to down with cost = 1 --> (3, 3) The total cost = 3.

Example 2:
Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).

Example 3:
Input: grid = [[1,2],[4,3]]
Output: 1

Example 4:
Input: grid = [[2,2,2],[2,2,2]]
Output: 3

Example 5:
Input: grid = [[4]]
Output: 0

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 100
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;
/*
Intuition
One observation is that, (not sure if it's obvious)
we can greedily explore the grid.
We will never detour the path to a node that we can already reach.

In the view of graph,
the fleche indicates a directed edge of weight = 0.
The distance between all neighbours are at most 1.
Now we want to find out the minimum distance between top-left and bottom-right.

Explanation
Find out all reachable nodes without changing anything.
Save all new visited nodes to a queue bfs.
Now iterate the queue
3.1 For each node, try changing it to all 3 other direction
3.2 Save the new reachable and not visited nodes to the queue.
3.3 repeat step 3

Complexity
Time O(NM)
Space O(NM)
*/
class Solution {
private:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m = 0;
    int n = 0;

    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& dp, int cost, queue<pair<int, int>>& q) {
        if (r < 0 || r >= m || c < 0 || c >= n || dp[r][c] != INT_MAX) {
            return;
        }

        dp[r][c] = cost;
        q.push(make_pair(r, c));
        int nextDir = grid[r][c] - 1;
        dfs(grid, r + dir[nextDir][0], c + dir[nextDir][1], dp, cost, q);
    }

public:
    int minCost(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int cost = 0;
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        dfs(grid, 0, 0, dp, cost, q);
        while (!q.empty()) {
            cost++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                pair<int, int> p = q.front();
                q.pop();

                int r = p.first;
                int c = p.second;
                for (int j = 0; j < 4; j++) {
                    dfs(grid, r + dir[j][0], c + dir[j][1], dp, cost, q);
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
