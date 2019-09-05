/*
778. Swim in Rising Water
On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

Now rain starts to fall. At time t, the depth of the water everywhere is t.
You can swim from a square to another 4-directionally adjacent square if and only
if the elevation of both squares individually are at most t.
You can swim infinite distance in zero time.
Of course, you must stay within the boundaries of the grid during your swim.

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
Let's keep a priority queue of which square we can walk in next.
We always walk in the smallest one that is 4-directionally adjacent to ones we've visited.

When we reach the target, the largest number we've visited so far is the answer.
*/
struct T { // {height, row, col}
    int t;
    int x;
    int y;

    T (int a, int b, int c) : t (a), x (b), y (c){}

    bool operator< (const T& d) const {
        return t > d.t;
    }
};

class Solution {
private:
    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};
public:
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        int result = 0;

        priority_queue<T> pq;
        pq.push(T(grid[0][0], 0, 0));

        vector<vector<int>> seen(N, vector<int>(N, 0));
        seen[0][0] = 1;

        while (true) {
            auto p = pq.top();
            pq.pop ();

            result = max(result, p.t);
            if (p.x == N - 1 and p.y == N - 1) {
                return result;
            }

            for (auto& d : dir) {
                int i = p.x + d[0];
                int j = p.y + d[1];
                if (i >= 0 and i < N and j >= 0 and j < N and !seen[i][j]) {
                    seen[i][j] = 1;
                    pq.push(T(grid[i][j], i, j));
                }
            }
        }
    }
};

/*
Imagine the grid as a place with different elevations at different spot
and the elevation of each spot will be changed to max(t, original_elevation)
which means a spot with elevation 5 at beginning, the elevation won't change in first 5 seconds
but change to 6 at time 6 and so on so forth.

So what the problem ask is to find a path from (0,0) to (n - 1, n - 1)
and you can walk through the path unless the elevation of each spot along the path is the same,
which will be the evevation of highest spot at time 0

there are different paths from start to end, and the time takes will be the same as max elevation spot along each path
we need to find the path with minimum highest elevation.
*/
class Solution1 { // 5.02%
private:
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};

    // so dp[i][j] stores the best elevation path we have seen so far from start to current spot
    void dfs(vector<vector<int>>& grid, int row, int col, int elevation, vector<vector<int>> &dp) {
        if (row < 0 or col < 0 or row >= n or col >= n) {
            return;
        }
        if (elevation >= dp[row][col]) {
            /*
            * if the new elevation is larger than current dp value
            * which means the path is worse than previous one we have seen before
           */
            return;
        }

        elevation = max(elevation, grid[row][col]);
        dp[row][col] = elevation;
        for (int i = 1; i < diff.size(); ++i) {
            dfs(grid, row + diff[i], col + diff[i - 1], elevation, dp);
        }
    }
public:
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        dfs(grid, 0, 0, 0, dp);
        return dp[n - 1][n - 1];
    }
};
