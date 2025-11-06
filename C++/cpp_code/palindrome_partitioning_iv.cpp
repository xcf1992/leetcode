/*
1745. Palindrome Partitioning IV
https://leetcode.com/problems/palindrome-partitioning-iv/

Given a string s,
return true if it is possible to split the string s into three non-empty palindromic substrings.
Otherwise, return false.​​​​​

A string is said to be palindrome
if it the same string when reversed.

Example 1:
Input: s = "abcbdd"
Output: true
Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
Example 2:
Input: s = "bcbddxy"
Output: false
Explanation: s cannot be split into 3 palindromes.

Constraints:
3 <= s.length <= 2000
s consists only of lowercase English letters.
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
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            if (i >= n - 1) {
                continue;
            }

            dp[i][i + 1] = s[i] == s[i + 1] ? 1 : 0;
        }

        for (int k = 3; k <= n; k++) {
            // k is the length of substring
            for (int i = 0; i < n - k + 1; i++) {
                int j = k + i - 1;
                if (dp[i + 1][j - 1] == 1 && s[i] == s[j]) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        for (int i = 0; i <= n - 3; i++) {
            if (!dp[0][i]) {
                continue;
            }

            for (int j = i + 1; j <= n - 2; j++) {
                if (!dp[i + 1][j]) {
                    continue;
                }

                if (dp[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};