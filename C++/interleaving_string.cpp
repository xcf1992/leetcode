/*
97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
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
#include <numeric>
using namespace std;

// dp[i][j] means if we can form first i + j characters from s3 using first i character from s1 and first j characters from s2
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if (n1 + n2 != n3) {
            return false;
        }

        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n1; ++i) {
            dp[i][0] = dp[i - 1][0] && (s3[i - 1] == s1[i - 1]);
        }
        for (int j = 1; j <= n2; ++j) {
            dp[0][j] = dp[0][j - 1] && (s3[j - 1] == s2[j - 1]);
        }

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (dp[i - 1][j] and (s1[i - 1] == s3[i + j - 1])) {
                    dp[i][j] = true;
                }
                if (dp[i][j - 1] and (s2[j - 1] == s3[i + j - 1])) {
                    dp[i][j] = true;
                }
            }
        }
        return dp[n1][n2];
    }
};
