//
//  largest_plus_sign.cpp
//  C++
//
//  Created by Chenfu Xie on 2/11/18.
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
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>> grid(N, vector<int>(N, N));
        for (auto& mine : mines) {
            grid[mine[0]][mine[1]] = 0;
        }
        
        for (int i = 0; i < N; i++) {
            int l = 0, r = 0, u = 0, d = 0;
            for (int j = 0; j < N; j++) {
                grid[i][j] = min(grid[i][j], l = (grid[i][j] == 0 ? 0 : l + 1));
                grid[i][N - j - 1] = min(grid[i][N - j - 1], r = (grid[i][N - j - 1] == 0 ? 0 : r + 1));
                grid[j][i] = min(grid[j][i], u = (grid[j][i] == 0 ? 0 : u + 1));
                grid[N - j - 1][i] = min(grid[N - j - 1][i], d = (grid[N - j - 1][i] == 0 ? 0 : d + 1));
            }
        }
        
        int result = 0;
        for (vector<int>& row : grid) {
            for (int& num : row) {
                result = max(result, num);
            }
        }
        return result;
    }
};
