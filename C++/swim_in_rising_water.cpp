//
//  swim_in_rising_water.cpp
//  C++
//
//  Created by Chenfu Xie on 2/4/18.
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
public:
    int swimInWater(vector<vector<int>> &grid) {
        int m = grid.size();
        vector<vector<int>> dp(m, vector<int>(m, INT_MAX));
        helper(grid, 0, 0, 0, dp);
        return dp[m - 1][m - 1];
    }
    void helper(vector<vector<int>> &grid, int row, int col, int deep,
                vector<vector<int>> &dp) {
        deep = max(deep, grid[row][col]);
        if (dp[row][col] <= deep) {
            return;
        }
        dp[row][col] = deep;
        int m = grid.size();
        for (int i = 0; i < direction.size(); i++) {
            int x = row + direction[i][0];
            int y = col + direction[i][1];
            if (x >= 0 && x < m && y >= 0 && y < m) {
                helper(grid, x, y, dp[row][col], dp);
            }
        }
    }
    
private:
    vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
};
