//
//  contain_virus.cpp
//  C++
//
//  Created by Chenfu Xie on 1/24/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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

class Solution {
private:
    int process(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int count = 0;
        int result = 0;
        int color = -1;
        int row = -1;
        int col = -1;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && visited[i][j] == 0) {
                    int walls = 0;
                    int area = dfs(grid, visited, i, j, color, walls);
                    if (area > count) {
                        result = walls;
                        count = area;
                        row = i;
                        col = j;
                    }
                    color -= 1;
                }
            }
        }
        
        buildWall(grid, row, col);
        
        visited = vector<vector<int>>(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && visited[i][j] == 0) {
                    spread(grid, visited, i, j);
                }
            }
        }
        return result;
    }
    
    int dfs(vector<vector<int>>& grid, vector<vector<int>>& visited, int row, int col, int color, int& walls) {
        int m = grid.size();
        int n = grid[0].size();
        if (row < 0 || col < 0 || row >= m || col >= n || visited[row][col] == 1 || grid[row][col] == -1) {
            return 0;
        }
        
        int affected_area = 0;
        if (grid[row][col] == 0) {
            walls += 1;
            if (visited[row][col] == color) {
                return 0;
            }
            visited[row][col] = color;
            return 1;
        }
        visited[row][col] = 1;
        
        affected_area += dfs(grid, visited, row - 1, col, color, walls);
        affected_area += dfs(grid, visited, row + 1, col, color, walls);
        affected_area += dfs(grid, visited, row, col - 1, color, walls);
        affected_area += dfs(grid, visited, row, col + 1, color, walls);
        
        return affected_area;
    }
    
    void buildWall(vector<vector<int>>& grid, int row, int col) {
        int m = grid.size();
        int n = grid[0].size();
        if (row < 0 || col < 0 || row >= m || col >= n || grid[row][col] != 1) {
            return;
        }
        grid[row][col] = -1;
        
        buildWall(grid, row + 1, col);
        buildWall(grid, row - 1, col);
        buildWall(grid, row, col + 1);
        buildWall(grid, row, col - 1);
    }
    
    void spread(vector<vector<int>>& grid, vector<vector<int>>& visited, int row, int col) {
        int m = grid.size();
        int n = grid[0].size();
        if (row < 0 || col < 0 || row >= m || col >= n || visited[row][col]) {
            return;
        }
        
        if (grid[row][col] == 0) {
            grid[row][col] = 1;
            visited[row][col] = 1;
        }
        else if (grid[row][col] == 1) {
            visited[row][col] = 1;
            spread(grid, visited, row, col - 1);
            spread(grid, visited, row, col + 1);
            spread(grid, visited, row - 1, col);
            spread(grid, visited, row + 1, col);
        }
    }
public:
    int containVirus(vector<vector<int>>& grid) {
        int result = 0;
        while (true) {
            int walls = process(grid);
            if (walls == 0) {
                return result;
            }
            result += walls;
        }
    }
};
