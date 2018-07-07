/*

 We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.
 
 XX  <- domino
 
 XX  <- "L" tromino
 X
 Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.
 
 (In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)
 
 Example:
 Input: 3
 Output: 5
 Explanation:
 The five different ways are listed below, different letters indicates different tiles:
 XYZ XXZ XYY XXY XYY
 XYZ YYZ XZZ XYY XXY
 Note:
 
 N  will be in range [1, 1000].
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    int numTilings(int N) {
        int mod = 1e9 + 7;
        if (N == 1) {
            return 1;
        }
        if (N == 2) {
            return 2;
        }
        if (N == 3) {
            return 5;
        }
        vector<int> dp({1, 2, 5});
        for (int i = 4; i <= N; i++) {
            int num = (dp[2] * 2 % mod + dp[0] % mod) % mod;
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = num;
        }
        return dp[2];
    }
};
