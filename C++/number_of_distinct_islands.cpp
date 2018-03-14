/*
 Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 
 Count the number of distinct islands. An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.
 
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
#include <set>
using namespace std;

class Solution {
private:
    void dfs(int x, int y, char index, string& island, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        int m = grid.size();
        int n = grid[0].size();
        
        if (x + 1 < m && !visited[x + 1][y] && grid[x + 1][y] == 1) {
            island.push_back(index);
            island.push_back('d');
            visited[x + 1][y] = true;
            dfs(x + 1, y, index + 1, island, grid, visited);
        }
        if (x - 1 >= 0 && !visited[x - 1][y] && grid[x - 1][y] == 1) {
            island.push_back(index);
            island.push_back('u');
            visited[x - 1][y] = true;
            dfs(x - 1, y, index + 1, island, grid, visited);
        }
        if (y + 1 < n && !visited[x][y + 1] && grid[x][y + 1] == 1) {
            island.push_back(index);
            island.push_back('r');
            visited[x][y + 1] = true;
            dfs(x, y + 1, index + 1, island, grid, visited);
        }
        if (y - 1 >= 0 && !visited[x][y - 1] && grid[x][y - 1] == 1) {
            island.push_back(index);
            island.push_back('l');
            visited[x][y - 1] = true;
            dfs(x, y - 1, index + 1, island, grid, visited);
        }
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();
        unordered_set<string> shape;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    string island = "";
                    visited[i][j] = true;
                    dfs(i, j, '0', island, grid, visited);
                    if (shape.find(island) == shape.end()) {
                        shape.insert(island);
                    }
                }
            }
        }
        return shape.size();
    }
};
