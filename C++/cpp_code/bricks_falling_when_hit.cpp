/*
803. Bricks Falling When Hit

We have a grid of 1s and 0s; the 1s in a cell represent bricks.
A brick will not drop if and only if it is directly connected to the top of the grid,
or at least one of its (4-way) adjacent bricks will not drop.

We will do some erasures sequentially.
Each time we want to do the erasure at the location (i, j),
the brick (if it exists) on that location will disappear,
and then some other bricks may drop because of that erasure.

Return an array representing the number of bricks that will drop after each erasure in sequence.

Example 1:
Input:
grid = [[1,0,0,0],[1,1,1,0]]
hits = [[1,0]]
Output: [2]
Explanation:
If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.

Example 2:
Input:
grid = [[1,0,0,0],[1,1,0,0]]
hits = [[1,1],[1,0]]
Output: [0,0]
Explanation:
When we erase the brick at (1, 0),
the brick at (1, 1) has already disappeared due to the last move.
So each erasure will cause no bricks dropping.
Note that the erased brick (1, 0) will not be counted as a dropped brick.

Note:
The number of rows and columns in the grid will be in the range [1, 200].
The number of erasures will not exceed the area of the grid.
It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
An erasure may refer to a location with no brick - if it does, no bricks drop.
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
#include <numeric>
using namespace std;

/*
using union-find reversely
*/
class Solution {
private:
    int m = 0;
    int n = 0;

    int unin(vector<int>& parent, vector<int>& count, int pos1, int pos2) {
        while (parent[pos1] != pos1) {
            pos1 = parent[pos1];
        }
        while (parent[pos2] != pos2) {
            pos2 = parent[pos2];
        }

        if (pos1 == pos2) {
            return 0;  // no bricks status changed
        }

        if (pos1 < n or pos2 >= n) {
            // component1 is attached to ceiling, we will attach component 2 to it and return the size of component 2
            parent[pos2] = pos1;
            count[pos1] += count[pos2];
            return (pos1 < n and pos2 >= n) ? count[pos2] : 0;
        }

        // pos1 >= n and pos2 < n
        parent[pos1] = pos2;
        count[pos2] += count[pos1];
        return count[pos1];
    }

    /*
     * This func is used to union neighbors and calculate the count of bricks that have been unioned to ceiling
     * Note that if this is iterating from left-top to right-bottom, we only need to union current with left and top
     * So union4 is a flag determining if we go thru 4 neighbors or just 2;
     *
     * basically it is used to update size of each component
     * and return count of increased brickes become attached to ceiling
     *
     * union4 == false means we are initializing
     */
    int addBricks(vector<vector<int>>& grid, vector<int>& parent, vector<int>& count, int row, int col, bool union4) {
        int pos = row * n + col;
        parent[pos] = pos;
        count[pos] = 1;
        /*
         * if key is at ceiling, init count as 1, because this brick has already been fixed.
         * so we will not count this extra brick when we attached component to ceiling
         * which makes the later adjust -= 1 incorrect in this case if we initialize added as 0
         */
        int added = pos < n ? 1 : 0;
        if (row > 0 and grid[row - 1][col] == 1) {
            added += unin(parent, count, pos - n, pos);
        }
        if (col > 0 and grid[row][col - 1] == 1) {
            added += unin(parent, count, pos - 1, pos);
        }
        if (union4 and row < m - 1 and grid[row + 1][col] == 1) {
            added += unin(parent, count, pos + n, pos);
        }
        if (union4 and col < n - 1 and grid[row][col + 1] == 1) {
            added += unin(parent, count, pos + 1, pos);
        }
        added -= 1;  // remove the added brick itself if we have some brickes become attched to ceiling.
        return max(0, added);
    }

public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        m = grid.size();
        if (m == 0) {
            return {};
        }
        n = grid[0].size();

        for (vector<int>& hit : hits) {
            grid[hit[0]][hit[1]] -= 1;
        }

        vector<int> parent(m * n, 0);
        // Union find set, ufs[key] is key's parent, thru which we can find root recursively
        vector<int> count(m * n, 0);  // Number of nodes in this set, only stored at the root node
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] < 1) {
                    continue;
                }
                addBricks(grid, parent, count, i, j, false);
            }
        }

        vector<int> result(hits.size(), 0);
        for (int k = hits.size() - 1; k >= 0; --k) {
            vector<int> hit = hits[k];
            grid[hit[0]][hit[1]] += 1;
            if (grid[hit[0]][hit[1]] > 0) {
                result[k] = addBricks(grid, parent, count, hit[0], hit[1], true);
            }
        }
        return result;
    }
};

// TLE
class Solution1 {
private:
    vector<vector<int>> vst = vector<vector<int>>(201, vector<int>(201));
    int n, m, id;

    bool valid(int r, int c) {
        return 0 <= r and r < n and 0 <= c and c < m;
    }

    bool falling(int r, int c, vector<vector<int>>& g, unordered_set<int>& connected) {
        if (!valid(r, c) or !g[r][c] or vst[r][c] == id) {
            return true;
        }

        if (r == 0) {
            return false;
        }

        vst[r][c] = id;
        connected.insert(r * m + c);
        vector<int> dr({-1, 0, 1, 0});
        vector<int> dc({0, 1, 0, -1});
        for (int d = 0; d < 4; ++d) {
            if (!falling(r + dr[d], c + dc[d], g, connected)) {
                return false;
            }
        }
        return true;
    }

public:
    vector<int> hitBricks(vector<vector<int>>& g, vector<vector<int>>& hits) {
        n = g.size();
        m = g[0].size();

        vector<int> dr({-1, 0, 1, 0});
        vector<int> dc({0, 1, 0, -1});
        vector<int> result;
        for (auto hit : hits) {
            if (g[hit[0]][hit[1]] == 0) {
                result.push_back(0);
                continue;
            }

            g[hit[0]][hit[1]] = 0;
            int drop = 0;
            for (int d = 0; d < 4; d++) {
                int x = hit[0] + dr[d];
                int y = hit[1] + dc[d];
                ++id;  // mark each connecting parts with a unique id in this run
                unordered_set<int> connected;
                if (falling(x, y, g, connected)) {
                    // if we find one brick will drop, then it mean all bricks connected to this brick will drop
                    // otherwise this brick will not drop itself.
                    drop += connected.size();
                    for (auto& pos : connected) {
                        g[pos / m][pos % m] = 0;
                    }
                }
            }
            result.push_back(drop);
        }
        return result;
    }
};