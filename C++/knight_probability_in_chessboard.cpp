//
//  knight_probability_in_chessboard.cpp
//  C++
//
//  Created by Chenfu Xie on 1/20/18.
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
    int movement[8][2] = {{1, 2},{1, -2},{-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1},{-2, -1}};
    
    double calculate(vector<vector<vector<double>>>& dp, int N, int K, int r, int c) {
        if (K == 0) {
            return 1.0;
        }
        
        if (dp[K][r][c] != 0.0) {
            return dp[K][r][c];
        }
        
        for (auto& i : movement) {
            if(r + i[0] < N && r + i[0] >= 0 && c + i[1] < N && c + i[1] >= 0) {
                dp[K][r][c] += calculate(dp, N, K - 1, r + i[0], c + i[1]);
            }
        }
        return dp[K][r][c];
    }
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<vector<double>>> dp(K+1, vector<vector<double>>(N, vector<double>(N, 0.0)));
        return calculate(dp, N, K, r, c) / pow(8, K);
    }

};
