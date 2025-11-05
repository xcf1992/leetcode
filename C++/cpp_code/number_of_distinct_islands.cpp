/*
694. Number of Distinct Islands
https://leetcode.com/problems/number-of-distinct-islands/

Given a non-empty 2D array grid of 0's and 1's,
an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands.
An island is considered to be the same as another if and only if one island can be translated
(and not rotated or reflected) to equal the other.

Example 1:
11000
11000
00011
00011
Given the above grid map, return 1.

Example 2:
11011
10000
00001
11011
Given the above grid map, return 3.

Notice that:
11
1
and
1
11
are considered different island shapes, because we do not consider reflection / rotation.

Note:
The length of each dimension in the given grid does not exceed 50.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;

    void dfs(int x, int y, char index, string &island, vector<vector<int> > &grid, vector<vector<bool> > &visited,
             map<char, pair<int, int> > &direction) {
        for (auto it = direction.begin(); it != direction.end(); ++it) {
            char dir = it->first;
            pair<int, int> diff = it->second;
            int row = x + diff.first;
            int col = y + diff.second;
            if (row >= m or row<0 or col >= n or col < 0 or grid[row][col] == 0 or visited[row][col]
            )
            {
                continue;
            }

            island.push_back(index);
            island.push_back(dir);
            visited[row][col] = true;
            dfs(row, col, index + 1, island, grid, visited, direction);
        }
    }

public:
    int numDistinctIslands(vector<vector<int> > &grid) {
        m = grid.size();
        if (m == 0) {
            return 0;
        }
        n = grid[0].size();

        map<char, pair<int, int> > direction;
        direction['d'] = {-1, 0};
        direction['u'] = {1, 0};
        direction['r'] = {0, 1};
        direction['l'] = {0, -1};

        unordered_set<string> shape;
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 or visited[i][j]
                )
                {
                    continue;
                }

                string island = "";
                visited[i][j] = true;
                dfs(i, j, '0', island, grid, visited, direction);
                shape.insert(island);
            }
        }
        return shape.size();
    }
};