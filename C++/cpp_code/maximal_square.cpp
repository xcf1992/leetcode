/*
221. Maximal Square

Given a 2D binary matrix filled with 0's and 1's,
find the largest square containing only 1's and return its area.

Example:
Input:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Output: 4
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

// dp(i,j) represents the side length of the maximum square whose bottom right corner is the cell with index (i,j)
class Solution {
public:
    int maximalSquare(vector<vector<char> > &matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();

        vector<vector<int> > dp(m, vector<int>(n, 0));
        int length = 0;
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] - '0';
            length = max(length, dp[0][j]);
        }
        for (int i = 0; i < m; i++) {
            dp[i][0] = matrix[i][0] - '0';
            length = max(length, dp[i][0]);
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++)
                if (matrix[i][j] == '1') {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                    length = max(length, dp[i][j]);
                }
        }
        return length * length;
    }
};

class Solution1 {
private:
    int square(int x, int y, int length, vector<vector<char> > &matrix) {
        int result = 1;
        int bot = x + 1;
        int maxLength = length;
        while (bot < matrix.size() and matrix[bot][y]
        ==
        '1'
        and bot
        -x < length
        )
        {
            int right = y + 1;
            while (right < matrix[0].size() and right
            -y < length
            and matrix[bot][right]
            ==
            '1'
            )
            {
                right += 1;
            }
            maxLength = min(maxLength, right - y);
            int curLen = min(bot - x + 1, maxLength);
            result = max(result, curLen * curLen);
            bot += 1;
        }
        return result;
    }

public:
    int maximalSquare(vector<vector<char> > &matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    int right = j;
                    while (right < n and matrix[i][right]
                    ==
                    '1'
                    )
                    {
                        right += 1;
                    }
                    result = max(result, square(i, j, right - j, matrix));
                }
            }
        }
        return result;
    }
};