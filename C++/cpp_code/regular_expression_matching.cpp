/*
10. Regular Expression Matching
https://leetcode.com/problems/regular-expression-matching/

Given an input string (s) and a pattern (p),
implement regular expression matching with support for '.' and '*'.
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
We define the dp DP[i][j] to be true if s[0..i) matches p[0..j) and false otherwise. Then the dp equations are:

if p[j - 1] != '*' and (s[i - 1] == p[j - 1] or p[j - 1] == '.')
    DP[i][j] = DP[i - 1][j - 1]

if p[j - 1] == '*' and the pattern repeats for 0 times
    DP[i][j] = DP[i][j - 2]

if p[j - 1] == '*' and the pattern repeats for at least 1 times.
    DP[i][j] = DP[i - 1][j] and (s[i - 1] == p[j - 2] or p[j - 2] == '.')
*/
/*
1, If p.charAt(j) == s.charAt(i) :
   dp[i][j] = dp[i-1][j-1];

2, If p.charAt(j) == '.' :
   dp[i][j] = dp[i-1][j-1];

3, If p.charAt(j) == '*':
   here are two sub conditions:
   if p.charAt(j-1) != s.charAt(i) :
      dp[i][j] = dp[i][j-2]  //in this case, a* only counts as empty
   if p.charAt(j-1) == s.charAt(i) or p.charAt(j-1) == '.':
      dp[i][j] = dp[i-1][j]    //in this case, a* counts as multiple a
                 or dp[i][j-1]   // in this case, a* counts as single a
                 or dp[i][j-2]   // in this case, a* counts as empty
*/
/*
 * f[i][j]: if s[0..i-1] matches p[0..j-1]
 * if p[j - 1] != '*'
 *      f[i][j] = f[i - 1][j - 1] and s[i - 1] == p[j - 1]
 * if p[j - 1] == '*', denote p[j - 2] with x
 *      f[i][j] is true iff any of the following is true
 *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
 *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x and f[i - 1][j]
 * '.' matches any single character
 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        dp[0][0] = true;
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                if (dp[0][j - 1] or (j > 1 and dp[0][j - 2])) {
                    dp[0][j] = true;
                }
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] != '*') {
                    dp[i][j] = dp[i - 1][j - 1] and (s[i - 1] == p[j - 1] or p[j - 1] == '.');
                } else {
                    if (s[i - 1] != p[j - 2] and p[j - 2] != '.') {
                        dp[i][j] = dp[i][j - 2];
                    } else {
                        dp[i][j] = dp[i][j - 2] or dp[i][j - 1] or dp[i - 1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};