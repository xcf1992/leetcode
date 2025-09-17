/*
44. Wildcard Matching

Given an input string (s) and a pattern (p),
implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.

Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Example 4:
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

Example 5:
Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    /*
    * 0: reach the end of s but unmatched
    * 1: unmatched without reaching the end of s
    * 2: matched
    */
    int check(string& s, string& p, int si, int pi) {
        if (si == s.size() and pi == p.size()) {
            return 2;
        }

        if (si == s.size() and p[pi] != '*') {
            return 0;
        }

        if (pi == p.size()) {
            return 1;
        }

        if (p[pi] == '*') {
            if (pi + 1 < p.size() and p[pi + 1] == '*') {
                return check(s, p, si, pi + 1);
            }
            for (int i = 0; i + si <= s.size(); ++i) {
                int result = check(s, p, si + i, pi + 1);
                if (result == 2 or result == 0) {
                    return result;
                }
            }
        }

        if (p[pi] == '?' or s[si] == p[pi]) {
            return check(s, p, si + 1, pi + 1);
        }
        return 1;
    }
public:
    bool isMatch(string s, string p) {
        return check(s, p, 0, 0) == 2;
    }
};

class Solution1 { // dp
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        dp[0][0] = true;
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*'){
                dp[0][j] = true;
            }
            else {
                break;
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] != '*') {
                    dp[i][j] = dp[i - 1][j - 1] and (s[i - 1] == p[j - 1] or p[j - 1]== '?');
                }
                else {
                    dp[i][j] = dp[i - 1][j] or dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};
