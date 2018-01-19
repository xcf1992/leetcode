//
//  maximum_length_of_repeated_subarray.cpp
//  C++
//
//  Created by Chenfu Xie on 1/18/18.
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
using namespace std;

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        int result = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    result = max(result, dp[i][j]);
                }
            }
        }
        return result;
    }
};
