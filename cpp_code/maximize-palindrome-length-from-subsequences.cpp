/*
1771. Maximize Palindrome Length From Subsequences
https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/

You are given two strings, word1 and word2.
You want to construct a string in the following manner:

Choose some non-empty subsequence subsequence1 from word1.
Choose some non-empty subsequence subsequence2 from word2.
Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the described manner.
If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made
by deleting some (possibly none) characters from s without changing the order of the remaining characters.

A palindrome is a string that reads the same forward as well as backward.

Example 1:
Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
Example 2:
Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a palindrome.
Example 3:
Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so return 0.

Constraints:
1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.
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
private:
    int longestPalindromeSubseq(string s, vector<vector<int> > &dp)
    {
        for (int len = 1; len <= s.size(); ++len) {
            for (int i = 0; i + len <= s.size(); ++i) {
                dp[i][i + len] = s[i] == s[i + len - 1] ?
                                            dp[i + 1][i + len - 1] + (len == 1 ? 1 : 2) :
                                            max(dp[i][i + len - 1], dp[i + 1][i + len]);
            }
        }
        return dp[0][s.size()];
    }
public:
    int longestPalindrome(string w1, string w2) {
        int sz = w1.size() + w2.size();
        int res = 0;
        vector<vector<int> > dp(sz + 1, vector<int>(sz + 1));

        longestPalindromeSubseq(w1 + w2, dp);

        for (int i = 0; i < w1.size(); ++i) {
            for (int j = w2.size() - 1; j >= 0; --j) {
                if (w1[i] == w2[j]) {
                    res = max(res, dp[i][w1.size() + j + 1]);
                    break;
                }
            }
        }
        return res;
    }
};
