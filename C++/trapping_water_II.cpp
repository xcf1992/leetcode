//
//  trapping_water_II.cpp
//  C++
//
//  Created by Chenfu Xie on 2/7/18.
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
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m < 3) {
            return 0;
        }
        int n = heightMap[0].size();
        if (n < 3) {
            return 0;
        }
        vector<vector<int>> left(m, vector<int>(n, 0));
        vector<vector<int>> right(m, vector<int>(n, 0));
        vector<vector<int>> up(m, vector<int>(n, 0));
        vector<vector<int>> down(m, vector<int>(n, 0));
        
        for (int i = 1; i < m; i++) {
            left[i][0] = heightMap[i][0];
            right[i][n - 1] = heightMap[i][n - 1];
            for (int j = 1; j < n; j++) {
                left[i][j] = max(left[i][j - 1], heightMap[i][j]);
                right[i][n - j - 1] = max(right[i][n - j], heightMap[i][n - j - 1]);
            }
        }
        
        for (int j = 1; j < n; j++) {
            up[0][j] = heightMap[0][j];
            down[m - 1][j] = heightMap[m - 1][j];
            for (int i = 1; i < m; i++) {
                up[i][j] = max(up[i - 1][j], heightMap[i][j]);
                down[m - i - 1][j] = max(down[m - i][j], heightMap[m - i - 1][j]);
            }
        }
        
        int result = 0;
        vector<vector<int>> waterMap(m, vector<int>(n, 0));
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                int wall = min(min(left[i][j], right[i][j]), min(up[i][j], down[i][j]));
                if (wall > heightMap[i][j]) {
                    result += wall - heightMap[i][j];
                    waterMap[i][j] = wall - heightMap[i][j];
                }
            }
        }
        
        bool spilled = true;
        vector<int> rowOffset({-1,1,0,0});
        vector<int> colOffset({0,0,1,-1});
        while (spilled) {
            spilled = false;
            
            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    if (waterMap[i][j] != 0) {
                        for (int move = 0; move < 4; move++) {
                            int row = i + rowOffset[move];
                            int col = j + colOffset[move];
                            int curWater = waterMap[i][j] + heightMap[i][j];
                            int neighbor = waterMap[row][col] + heightMap[row][col];
                            if (curWater > neighbor) {
                                spilled = true;
                                int spillWater = curWater - max(neighbor, heightMap[i][j]);
                                waterMap[i][j] = waterMap[i][j] - spillWater;
                                result -= spillWater;
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
};

