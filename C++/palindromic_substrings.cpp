/*
647. Palindromic Substrings
https://leetcode.com/problems/palindromic-substrings/

Given a string, your task is to count how many palindromic substrings in this string.
The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Note:
The input string length won't exceed 1000.
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

class Solution1 {
public:
    int countSubstrings(string s) {
        int len = s.size();

        int result = len;
        for (int mid = 0; mid < len; mid++) {
            int left = mid - 1;
            int right = mid + 1;
            while (left >= 0 and right < len and s[left] == s[right]) {
                result += 1;
                left -= 1;
                right += 1;
            }
        }

        for (int midLeft = 0, midRight = 1; midRight < len; ++midLeft, ++midRight) {
            int left = midLeft;
            int right = midRight;
            while (left >= 0 and right < len and s[left] == s[right]) {
                result += 1;
                left -= 1;
                right += 1;
            }
        }
        return result;
    }
};

class Solution { // dp
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += 1;
            dp[i][i] = true;
            if (i > 0 and s[i] == s[i - 1]) {
                result += 1;
                dp[i - 1][i] = true;
            }
        }

        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j] and dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    result += 1;
                }
            }
        }
        return result;
    }
};
