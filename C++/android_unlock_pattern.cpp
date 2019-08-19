/*
351. Android Unlock Patterns
Given an Android 3x3 key lock screen and two integers m and n,
where 1 ≤ m ≤ n ≤ 9, count the total number of unlock patterns of the Android lock screen,
which consist of minimum of m keys and maximum n keys.

Rules for a valid pattern:
Each pattern must connect at least m keys and at most n keys.
All the keys must be distinct.
If the line connecting two consecutive keys in the pattern passes through any other keys,
the other keys must have previously selected in the pattern. No jumps through non selected key is allowed.
The order of keys used matters.

Explanation:
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
Invalid move: 4 - 1 - 3 - 6
Line 1 - 3 passes through key 2 which had not been selected in the pattern.

Invalid move: 4 - 1 - 9 - 2
Line 1 - 9 passes through key 5 which had not been selected in the pattern.

Valid move: 2 - 4 - 1 - 3 - 6
Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern

Valid move: 6 - 5 - 4 - 1 - 9 - 2
Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.

Example:
Given m = 1, n = 1, return 9.

Note:
If try on ur android phone, 1-8 won’t actually touch 4 and 5 because each number is represented by dot … not the square as illustrated …
so I guess the illustration should be corrected
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
using namespace std;

class Solution {
private:
    int dfs(vector<bool>& visited, vector<vector<int>>& skip, int curDigit, int remain) {
        if (remain == 0) {
            return 1;
        }

        int result = 0;
        visited[curDigit] = true;
        for (int i = 1; i <= 9; i++) {
            if (!visited[i] and (skip[curDigit][i] == 0 || visited[skip[curDigit][i]])) {
                result += dfs(visited, skip, i, remain - 1);
            }
        }
        visited[curDigit] = false;
        return result;
    }
public:
    int numberOfPatterns(int m, int n) {
        vector<vector<int>> skip(10, vector<int>(10, 0));
        skip[1][3] = skip[3][1] = 2;
        skip[1][7] = skip[7][1] = 4;
        skip[3][9] = skip[9][3] = 6;
        skip[7][9] = skip[9][7] = 8;
        skip[1][9] = skip[9][1] = skip[2][8] = skip[8][2] = skip[3][7] = skip[7][3] = skip[4][6] = skip[6][4] = 5;

        vector<bool> visited(10, false);
        int result = 0;
        for (int i = m; i <= n; i++) {
            result += dfs(visited, skip, 1, i - 1) * 4; // 1, 3, 7, 9 are symmetric
            result += dfs(visited, skip, 2, i - 1) * 4; // 2, 4, 6, 8 are symmetric
            result += dfs(visited, skip, 5, i - 1); // 5
        }
        return result;
    }
};
