//
//  perfect_squares.cpp
//  C++
//
//  Created by Chenfu Xie on 1/31/18.
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
    void find(int target, int curSum, int start, int count, int& result) {
        if (curSum == target) {
            result = min(result, count);
        }
        
        for (int i = start; i > 0; i--) {
            curSum += i * i;
            if (curSum <= target) {
                find(target, curSum, i, count + 1, result);
            }
            curSum -= i * i;
        }
    }
public:
    int numSquares(int n) {
        int result = n;
        int start = sqrt(n);
        find(n, 0, start, 0, result);
        return result;
    }
};

class Solution2 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        for (int i = 1; i <= sqrt(n); i++) {
            dp[i * i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (dp[i] == INT_MAX) {
                for (int j = 1; j < i; j++) {
                    dp[i] = min(dp[i], dp[j] + dp[i - j]);
                }
            }
        }
        return dp.back();
    }
};

class Solution3 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        for (int i = 1; i <= sqrt(n); i++) {
            dp[i * i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (dp[i] == INT_MAX) {
                for (int j = 1; j * j < i; j++) {
                    dp[i] = min(dp[i], 1 + dp[i - j * j]);
                }
            }
        }
        return dp.back();
    }
};
