/*
https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
1930. Unique Length-3 Palindromic Subsequences

Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted
without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".


Example 1:

Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")
Example 2:

Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".
Example 3:

Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")


Constraints:

3 <= s.length <= 105
s consists of only lowercase English letters.
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<int> first_idx(26, -1);
        vector<int> last_idx(26, -1);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first_idx[c] == -1) {
                first_idx[c] = i;
            }
            last_idx[c] = i;
        }

        int rst = 0;
        for (int i = 0; i < 26; i++) {
            if (first_idx[i] == -1 || last_idx[i] == -1 || first_idx[i] == last_idx[i]) {
                continue;
            }

            int left = first_idx[i];
            int right = last_idx[i];
            int cnt = 0;
            for (int j = left + 1; j <= right - 1; j++) {
                cnt |= 1 << (s[j] - 'a');
            }
            rst += __builtin_popcount(cnt);
        }
        return rst;
    }
};
