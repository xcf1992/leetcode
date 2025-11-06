/*
5. Longest Palindromic Substring
https://leetcode.com/problems/longest-palindromic-substring/

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: "cbbd"
Output: "bb"
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
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int maxLen = 1;
        int start = 0;
        for (int length = 0; length < n; length++) {
            for (int i = 0; i < n; i++) {
                int j = i + length;

                if (j >= n) {
                    break;
                }

                if (s[i] != s[j]) {
                    continue;
                }

                if (j - i < 3 || dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                }

                if (dp[i][j] && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

class Solution1 {
private:
    string expand(string s, int left, int right) {
        while (left >= 0 and right < s.size() and s[left] == s[right]) {
            left--;
            right++;
        }
        return s.substr(left + 1, right - left - 1);
    }

public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) {
            return s;
        }

        string result = s.substr(0, 1);
        for (int i = 0; i < s.size(); i++) {
            string p1 = expand(s, i, i);
            if (result.size() < p1.size()) {
                result = p1;
            }

            string p2 = expand(s, i, i + 1);
            if (result.size() < p2.size()) {
                result = p2;
            }
        }
        return result;
    }
};