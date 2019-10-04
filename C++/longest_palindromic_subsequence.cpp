/*
516. Longest Palindromic Subsequence
https://leetcode.com/problems/longest-palindromic-subsequence/

Given a string s, find the longest palindromic subsequence's length in s.
You may assume that the maximum length of s is 1000.

Example 1:
Input:
"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".

Example 2:
Input:
"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".
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
        vector<vector<int>> dp(s.size(), vector<int>(s.size()));
        for (int len = 1; len <= s.size(); len++) {
            for (int left = 0; left + len <= s.size(); left++) {
                int right = left + len - 1;
                if (left == right) {
                    dp[left][right] = 1;
                }
                else if (left + 1 == right) {
                    dp[left][right] = s[left] == s[right] ? 2 : 1;
                }
                else {
                    int temp = s[left] == s[right] ? 2 : 0;
                    dp[left][right] = max(dp[left + 1][right - 1] + temp, max(dp[left + 1][right], dp[left][right - 1]));
                }
            }
        }
        return dp[0].back();
    }
};