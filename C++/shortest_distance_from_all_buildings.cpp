/*
 You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:
 
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
 There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
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

class Solution {
private:
    void update(int house, int distance, int posI, int posJ, vector<vector<int>>& shortest, unordered_map<int, unordered_set<int>>& visited, queue<vector<int>>& bfs, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if (posI < 0 || posJ < 0 || posI >= m || posJ >= n || grid[posI][posJ] != 0) {
            return;
        }
        
        int newPos = posI * n + posJ;
        if (visited[newPos].find(house) != visited[newPos].end()) {
            return;
        }
        
        shortest[posI][posJ] += distance;
        visited[newPos].insert(house);
        bfs.push({house, distance, newPos});
    }
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        unordered_map<int, unordered_set<int>> visited; // pos hae been visited by house x
        queue<vector<int>> bfs; // insert pair <house, distance, pos> the distance house x reach pos
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
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int curHouse = bfs.front()[0];
                int curDistance = bfs.front()[1];
                int posI = bfs.front()[2] / n;
                int posJ = bfs.front()[2] % n;
                bfs.pop();
                
                update(curHouse, curDistance + 1, posI - 1, posJ, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI + 1, posJ, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI, posJ - 1, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI, posJ + 1, shortest, visited, bfs, grid);
            }
        }
        
        int result = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && visited[i * n + j].size() == house) {
                    result = min(result, shortest[i][j]);
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};
