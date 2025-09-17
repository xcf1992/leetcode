/*
1216. Valid Palindrome III
https://leetcode.com/problems/valid-palindrome-iii/

Given a string s and an integer k, find out if the given string is a K-Palindrome or not.
A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.

Example 1:
Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.

Constraints:
1 <= s.length <= 1000
s has only lowercase English letters.
1 <= k <= s.length
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
    int longestPalindromeSubsequenceLenth(string s) {
        int n = s.size();
        if (n <= 1) {
            return n;
        }

        vector<vector<int>> dp(n, vector<int>(n, 1)); // it will be at least for a single letter
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            if (i + 1 < n and s[i] == s[i + 1]) {
                dp[i][i + 1] = 2;
            }
        }

        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size();
        return n - longestPalindromeSubsequenceLenth(s) <= k;
    }
};
