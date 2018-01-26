//
//  split_array_largest_sum.cpp
//  C++
//
//  Created by Chenfu Xie on 1/25/18.
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
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        for (int i = 0; i < m; i++) {
            dp[i][0] = nums[0];
        }
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + nums[j];
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                int maxValue = dp[0][j];
                for (int k = 0; k < j; k++) {
                    maxValue = max(dp[0][j] - dp[0][k], dp[i - 1][k]);
                    dp[i][j] = min(maxValue, dp[i][j]);
                }
            }
        }
        
        return dp[m - 1][n - 1];
    }
};
