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
#include <set>
#include <numeric>
using namespace std;

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
            return 0; // no bricks status changed
        }
        
        if (pos1 < n or pos2 >= n) { // component1 is attached to ceiling, we will attach component 2 to it and return the size of component 2
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
        int added = pos < n ? 1 : 0; // if key is at ceiling, init count as 1, because this brick has already been fixed.
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
        added -= 1; // remove the added brick itself if we have some brickes become attched to ceiling.
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
        
        vector<int> parent(m * n, 0); // Union find set, ufs[key] is key's parent, thru which we can find root recursively
        vector<int> count(m * n, 0); // Number of nodes in this set, only stored at the root node
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

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {1,0,1},
        {0,0,1}
    });
    vector<vector<int>> matrix2({
        {1,0},
        {0,0}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.hitBricks(matrix, matrix2);
}
