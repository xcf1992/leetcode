//
//  toeplitz_matrix.cpp
//  C++
//
//  Created by Chenfu Xie on 1/21/18.
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
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        for (int j = 1; j < n; j++) {
            int x = m - 1;
            int y = j;
            int num = matrix[x][y];
            while (x >= 0 && y >= 0) {
                if (matrix[x][y] != num) {
                    return false;
                }
                x -= 1;
                y -= 1;
            }
        }
        return true;
    }
};
