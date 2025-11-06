/*
87. Scramble String
Hard

291

486

Favorite

Share
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
    // dp, even slower than simple recursively
public:
    bool isScramble(string s1, string s2) {
        int len = s1.size();
        /*
         * dp[i][j][k] identify if s1(i, i + 1, ... , i + k - 1) is scrambled as
         *                         s2(j, j + 1, ... , j + k - 1)
         */
        vector<vector<vector<bool>>> dp(len, vector<vector<bool>>(len, vector<bool>(len + 1, false)));
        for (int k = 1; k <= len; ++k) {
            for (int i = 0; i + k <= len; ++i) {
                for (int j = 0; j + k <= len; ++j) {
                    if (k == 1) {
                        dp[i][j][k] = s1[i] == s2[j];
                        continue;
                    }
                    for (int q = 1; q < k; ++q) {
                        if ((dp[i][j][q] and dp[i + q][j + q][k - q]) or
                            (dp[i][j + k - q][q] and dp[i + q][j][k - q])) {
                            dp[i][j][k] = true;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][0][len];
    }
};

class Solution2 {
    // check recursively with memo
private:
    unordered_map<string, unordered_map<string, bool>> memo;

public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }

        if (memo.find(s1) != memo.end() and memo[s1].find(s2) != memo[s1].end()) {
            return memo[s1][s2];
        }

        string temp1 = s1;
        sort(temp1.begin(), temp1.end());
        string temp2 = s2;
        sort(temp2.begin(), temp2.end());
        if (temp1 != temp2) {
            memo[s1][s2] = false;
            return false;
        }

        int len = s1.size();
        for (int l = 1; l < len; ++l) {
            if (isScramble(s1.substr(0, l), s2.substr(0, l)) and isScramble(s1.substr(l), s2.substr(l))) {
                memo[s1][s2] = true;
                return true;
            }
            if (isScramble(s1.substr(0, l), s2.substr(len - l)) and isScramble(s1.substr(l), s2.substr(0, len - l))) {
                memo[s1][s2] = true;
                return true;
            }
        }
        memo[s1][s2] = false;
        return false;
    }
};

class Solution1 {
    // check recursively
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }
        string temp1 = s1;
        sort(temp1.begin(), temp1.end());
        string temp2 = s2;
        sort(temp2.begin(), temp2.end());
        if (temp1 != temp2) {
            return false;
        }

        int len = s1.size();
        for (int l = 1; l < len; ++l) {
            if (isScramble(s1.substr(0, l), s2.substr(0, l)) and isScramble(s1.substr(l), s2.substr(l))) {
                return true;
            }
            if (isScramble(s1.substr(0, l), s2.substr(len - l)) and isScramble(s1.substr(l), s2.substr(0, len - l))) {
                return true;
            }
        }
        return false;
    }
};