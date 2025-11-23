/*
1682. Longest Palindromic Subsequence II

A subsequence of a string s is considered a good palindromic subsequence if:

It is a subsequence of s.
It is a palindrome (has the same value if reversed).
It has an even length.
No two consecutive characters are equal, except the two middle ones.
For example, if s = "abcabcabb", then "abba" is considered a good palindromic subsequence, while "bcb" (not even length)
and "bbbb" (has equal consecutive characters) are not.

Given a string s, return the length of the longest good palindromic subsequence in s.



Example 1:

Input: s = "bbabab"
Output: 4
Explanation: The longest good palindromic subsequence of s is "baab".
Example 2:

Input: s = "dcbccacdb"
Output: 4
Explanation: The longest good palindromic subsequence of s is "dccd".


Constraints:

1 <= s.length <= 250
s consists of lowercase English letters.
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
public:
    int longestPalindromeSubseq(string s) {
        const int n = s.length();
        // dp[i][j] = length of longest palindrome subseq in s[i:j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // edge[i][j] = edge of longest palindrome subseq in s[i:j]
        vector<vector<char>> edge(n, vector<char>(n));
        for (int len = 2; len <= n; ++len) {
            for (int l = 0 ; l + len - 1 < n; ++l) {
                int r = l + len - 1;
                // s[l] != edge[l + 1][r - 1]  ->  Exclude the case of two consecutive characters
                // len == 2  ->  Except the two middle ones
                if (s[l] == s[r] && (len == 2 || s[l] != edge[l + 1][r - 1])) {
                    dp[l][r] = 2 + dp[l + 1][r - 1];
                    edge[l][r] = s[l];
                } else if (dp[l][r - 1] > dp[l + 1][r]) {
                    dp[l][r] = dp[l][r - 1];
                    edge[l][r] = edge[l][r - 1];
                } else {
                    dp[l][r] = dp[l + 1][r];
                    edge[l][r] = edge[l + 1][r];
                }
            }
        }
        return dp[0][n - 1];
    }
};
