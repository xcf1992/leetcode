//
//  ones_and_zeros.cpp
//  C++
//
//  Created by Chenfu Xie on 1/22/18.
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
    vector<int> count(string num) {
        vector<int> result(2, 0);
        for (char c : num) {
            result[c - '0'] += 1;
        }
        return result;
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (string num : strs) {
            vector<int> digit = count(num);
            
            for (int i = m; i >= digit[0]; i--) {
                for (int j = n; j >= digit[1]; j--) {
                    dp[i][j] = max(dp[i - digit[0]][j - digit[1]] + 1, dp[i][j]);
                }
            }
        }
        return dp[m][n];
    }
};
