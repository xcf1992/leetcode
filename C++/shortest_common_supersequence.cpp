/*
1092. Shortest Common Supersequence

Given two strings str1 and str2,
return the shortest string that has both str1 and str2 as subsequences.
If multiple answers exist, you may return any of them.

(A string S is a subsequence of string T if deleting some number of characters from T
(possibly 0, and the characters are chosen anywhere from T) results in the string S.)

Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation:
str1 = "abac" is a substring of "cabac" because we can delete the first "c".
str2 = "cab" is a substring of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.

Note:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.
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
    string longestCommonSubsequence(string& str1, string& str2) {
        int n1 = str1.size();
        int n2 = str2.size();
        vector<vector<string>> dp(n1 + 1, vector<string>(n2 + 1, ""));
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + str1[i - 1];
                }
                else {
                    dp[i][j] = dp[i - 1][j].size() > dp[i][j - 1].size() ? dp[i - 1][j] : dp[i][j - 1];
                }
            }
        }
        return dp[n1][n2];
    }
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int i = 0;
        int j = 0;
        string lcs = longestCommonSubsequence(str1, str2);
        string result = "";
        for (char c : lcs) {
            while (i < str1.size() and c != str1[i]) {
                result.push_back(str1[i]);
                i += 1;
            }
            while (j < str2.size() and c != str2[j]) {
                result.push_back(str2[j]);
                j += 1;
            }
            result.push_back(c);
            i += 1;
            j += 1;
        }
        return result + str1.substr(i) + str2.substr(j); // remember to add the left part of each string
    }
};
