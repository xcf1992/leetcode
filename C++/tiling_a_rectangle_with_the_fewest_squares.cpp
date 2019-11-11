/*
1240. Tiling a Rectangle with the Fewest Squares
https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/

Given a rectangle of size n x m, find the minimum number of integer-sided squares that tile the rectangle.

Example 1:
Input: n = 2, m = 3
Output: 3
Explanation: 3 squares are necessary to cover the rectangle.
2 (squares of 1x1)
1 (square of 2x2)

Example 2:
Input: n = 5, m = 8
Output: 5

Example 3:
Input: n = 11, m = 13
Output: 6

Constraints:
1 <= n <= 13
1 <= m <= 13
*/
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
#include <set>
#include <numeric>
using namespace std;

// wrong answer 11, 13
class Solution {
private:
    int dfs(int n, int m, vector<vector<int>>& memo) {
        if (m == 0 or n == 0) {
            return 0;
        }

        if (m == n) {
            return 1;
        }

        if (memo[n][m] != INT_MAX) {
            return memo[n][m];
        }

        memo[n][m] = n * m;
        for (int len = 1; len < min(n, m); ++len) {
            memo[n][m] = min(memo[n][m], 1 + dfs(len, m - len, memo) + dfs(n - len, m, memo));
        }
        return memo[n][m];
    }
public:
    int tilingRectangle(int n, int m) {
        vector<vector<int>> memo(n + 1, vector<int>(m + 1, INT_MAX));
        return dfs(n, m, memo);
    }
};
