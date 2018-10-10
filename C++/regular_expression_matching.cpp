/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
This problem has a typical solution using Dynamic Programming.
We define the state DP[i][j] to be true if s[0..i) matches p[0..j) and false otherwise. Then the state equations are:

if p[j - 1] != '*' && (s[i - 1] == p[j - 1] || p[j - 1] == '.')
    DP[i][j] = DP[i - 1][j - 1]

if p[j - 1] == '*' and the pattern repeats for 0 times
    DP[i][j] = DP[i][j - 2]

if p[j - 1] == '*' and the pattern repeats for at least 1 times.
    DP[i][j] = DP[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.')
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size(); 
        vector<vector<bool> > dp(m + 1, vector<bool> (n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                }
                else {
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[m][n];
    }
};

class Solution1 {
public:
    bool isMatch(const char *s, const char *p) {
        if (s == nullptr) {
            return p == nullptr;
        }
        if (p == nullptr) {
            return false;
        }

        if (*p == '\0') {
            return *s == '\0';
        }

        if (*(p + 1) != '*') {
            if (*s == '\0') {
                return false;
            }
            if (*p == *s || *p == '.') {
                return isMatch(s + 1, p + 1);
            }
            return false;
        }
        else {
            while (*s != '\0' && (*p == *s || *p == '.')) {
                if (isMatch(s, p + 2)) {
                    return true;
                }
                s++;
            }
            return isMatch(s, p + 2);
        }
    }
};