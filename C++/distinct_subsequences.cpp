/*
115. Distinct Subsequences
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string
by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:

As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:

As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int lenS = s.size();
        int lenT = t.size();
        if (lenS <= 0 or lenT <= 0 or lenS < lenT) {
            return 0;
        }

        vector<vector<long>> dp(lenS + 1, vector<long>(lenT + 1, 0));
        for (int i = 0; i <= lenS; ++i) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= lenS; ++i) {
            for (int j = 1; j <= lenT and j <= i; ++j) {
                dp[i][j] = dp[i - 1][j]; // if we can construct first j letters from t using first i - 1 letters from s
                if (s[i - 1] == t[j - 1]) { // we use ith letter as last letter in s, then construct first j - 1 letters from t using first i - 1 letters from s
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return dp[lenS][lenT];
    }
};
