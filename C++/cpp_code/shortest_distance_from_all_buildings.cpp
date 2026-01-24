/*
https://leetcode.com/problems/shortest-distance-from-all-buildings/
317. Shortest Distance from All Buildings

You want to build a house on an empty land which reaches all buildings in the shortest amount of distance.
You can only move up, down, left and right.

You are given a 2D grid of values 0, 1 or 2, where:
Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.

Example:
Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
the point (1,2) is an ideal empty land to build a house, as the total
travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building.
If it is not possible to build such house according to the above rules, return -1.
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
    // 17.08%
private:
    int m = 0;
    int n = 0;

    void update(int house, int distance, int row, int col, vector<vector<int>>& shortest,
                unordered_map<int, unordered_set<int>>& visited, queue<vector<int>>& bfs, vector<vector<int>>& grid) {
        if (row < 0 or col < 0 or row >= m or col >= n or grid[row][col] != 0) {
            return;
        }

        int pos = row * n + col;
        if (visited[pos].find(house) != visited[pos].end()) {
            return;
        }

        shortest[row][col] += distance;
        visited[pos].insert(house);
        bfs.push({house, distance, pos});
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        unordered_map<int, unordered_set<int>> visited;  // pos has been visited by house x
        queue<vector<int>> bfs;  // insert pair <house, distance, pos> the distance house x reach pos
        int house = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    bfs.push({house, 0, i * n + j});
                    visited[i * n + j].insert(house);
                    house += 1;
                }
            }
        }

        vector<vector<int>> shortest(m, vector<int>(n, 0));
        vector<int> diff = {0, 1, 0, -1, 0};
        while (!bfs.empty()) {
            int cur_house = bfs.front()[0];
            int cur_distance = bfs.front()[1];
            int cur_row = bfs.front()[2] / n;
            int cur_col = bfs.front()[2] % n;
            bfs.pop();

            for (int k = 1; k < diff.size(); ++k) {
                update(cur_house, cur_distance + 1, cur_row + diff[k], cur_col + diff[k - 1], shortest, visited, bfs,
                       grid);
            }
        }

        int result = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 and visited[i * n + j].size() == house) {
                    result = min(result, shortest[i][j]);
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};

class Solution {
private:
    void bfs(vector<vector<int>>& grid, vector<vector<vector<int>>>& distances, int row, int col) {
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int rows = grid.size(), cols = grid[0].size();

        // Queue to do a bfs, starting from each cell located at (r,c).
        queue<pair<int, int>> q;
        q.push({row, col});

        // Keep track of visited cells.
        vector<vector<bool>> vis(rows, vector<bool>(cols, false));
        vis[row][col] = true;

        int steps = 0;
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                auto curr = q.front();
                q.pop();
                row = curr.first;
                col = curr.second;

                // If we reached an empty cell, then add the distance
                // and increment the count of houses reached at this cell.
                if (grid[row][col] == 0) {
                    distances[row][col][0] += steps;
                    distances[row][col][1] += 1;
                }

                // Traverse the next cells which is not a blockage.
                for (auto& dir : dirs) {
                    int nextRow = row + dir[0];
                    int nextCol = col + dir[1];
                    if (nextRow >= 0 && nextCol >= 0 && nextRow < rows && nextCol < cols) {
                        if (!vis[nextRow][nextCol] && grid[nextRow][nextCol] == 0) {
                            vis[nextRow][nextCol] = true;
                            q.push({nextRow, nextCol});
                        }
                    }
                }
            }

            // After traversing one level cells, increment the steps by 1.
            steps++;
        }
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int minDistance = INT_MAX;
        int rows = grid.size();
        int cols = grid[0].size();
        int totalHouses = 0;

        // Store { total_dist, houses_count } for each cell.
        vector<vector<vector<int>>> distances(rows, vector<vector<int>>(cols, {0, 0}));

        // Count houses and start bfs from each house.
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 1) {
                    totalHouses++;
                    bfs(grid, distances, row, col);
                }
            }
        }

        // Check all empty lands with houses count equal to total houses and find the min ans.
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (distances[row][col][1] == totalHouses) {
                    minDistance = min(minDistance, distances[row][col][0]);
                }
            }
        }

        // If we haven't found a valid cell return -1.
        if (minDistance == INT_MAX) {
            return -1;
        }
        return minDistance;
    }
};