/*
https://leetcode.com/problems/wildcard-matching/description/
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

/*
Next, we initialize the base cases. There are three base cases:

When both the string and the pattern are empty.
Always match. dp[0][0] = true;
When only the string is empty.
Only if the subpattern only consists of *, we have a match.
When only the pattern is empty.
Always not match.
There are two special characters that we need to take special care in the pattern.

?
This is actually easy to deal with. Everytime when we encounter this, we can consider it matches with any character in
the string. Say we are currently at dp[i][j], and we have p[j - 1] == '?', then we know it matches with s[i - 1], no
matter what s[i - 1] actually is.
*
This is slightly hard to deal with. A small technique while dealing this kind of question is to actually draw out the dp
table, and try to fill out the table manually, when the state transfer function is not very straightforward. Everything
will become much clearer after you fill out one row or two. When we encounter a * in the pattern, and assuming that
we're currently trying to figure out what dp[i][j] is. Then we need to consider two cases if p[j - 1] == '*'. Is dp[i -
1][j] true? If yes, it means the current subpattern p[0...j - 1] we have matches the substring s[0... i - 2]. Then will
p[0...j - 1] match with s[0... i - 1]? The answer is yes, because * can match any sequence of characters, so it's able
to match one more character s[i - 1]. Is dp[i][j - 1] true? If yes, it just means the current substring s[0...i - 1]
matches with the subpattern p[0...j - 2]. Therefore, if we add one more * into the subpattern, it will also match as *
can match empty subsequence.
 */
class Solution1 {
    // dp
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        dp[0][0] = true;
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = true;
            } else {
                break;
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] != '*') {
                    dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '?');
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};