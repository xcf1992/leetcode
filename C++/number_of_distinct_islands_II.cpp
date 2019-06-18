/*
 711. Number of Distinct Islands II

 Given a non-empty 2D array grid of 0's and 1's, 
 an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
 You may assume all four edges of the grid are surrounded by water.

 Count the number of distinct islands. 
 An island is considered to be the same as another if they have the same shape, 
 or have the same shape after rotation (90, 180, or 270 degrees only) or reflection (left/right direction or up/down direction).

 Example 1:
 11000
 10000
 00001
 00011
 Given the above grid map, return 1.

 Notice that:
 11
 1
 and
 1
 11
 are considered same island shapes. Because if we make a 180 degrees clockwise rotation on the first island, then two islands will have the same shapes.
 Example 2:
 11100
 10001
 01001
 01110
 Given the above grid map, return 2.

 Here are the two distinct islands:
 111
 1
 and
 1
 1

 Notice that:
 111
 1
 and
 1
 111
 are considered same island shapes. Because if we flip the first array in the up/down direction, then they have the same shapes.
 Note: The length of each dimension in the given grid does not exceed 50.
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
#include <set>
using namespace std;

class Solution {
private:
    unordered_map<int, vector<pair<int, int>>> shape;

    void dfs(int row, int col, vector<vector<int>> &grid, int mark) {
        if (row < 0 or col < 0 or row >= grid.size() or col >= grid[0].size() or grid[row][col] != 1) {
            return;
        }

        grid[row][col] = mark;
        shape[mark].push_back({row, col});
        dfs(row + 1, col, grid, mark);
        dfs(row - 1, col, grid, mark);
        dfs(row, col - 1, grid, mark);
        dfs(row, col + 1, grid, mark);
    }

    vector<pair<int, int>> normalize(vector<pair<int, int>> island) {
        vector<vector<pair<int, int>>> islands(8);
        for (pair<int, int> node : island) {
            int x = node.first;
            int y = node.second;
            islands[0].push_back({x, y});
            islands[1].push_back({x, -y});
            islands[2].push_back({-x, y});
            islands[3].push_back({-x, -y});
            islands[4].push_back({y, x});
            islands[5].push_back({y, -x});
            islands[6].push_back({-y, x});
            islands[7].push_back({-y, -x});
        }

        for (vector<pair<int, int>>& is : islands) {
            sort(is.begin(), is.end());
        }

        for (vector<pair<int, int>>& is : islands) {
            for (int i = 1; i < is.size(); ++i) {
                is[i].first -= is[0].first;
                is[i].second -= is[0].second;
            }
            is[0] = {0, 0};
        }

        sort(islands.begin(), islands.end());
        return islands[0];
    }
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int mark = 2;
        set<vector<pair<int, int>>> result;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 1) {
                    dfs(i, j, grid, mark);
                    result.insert(normalize(shape[mark]));
                    mark += 1;
                }
            }
        }
        return result.size();
    }
};
