/*
1641. Count Sorted Vowel Strings
https://leetcode.com/problems/count-sorted-vowel-strings/

Given an integer n,
return the number of strings of length n that consist only of vowels (a, e, i, o, u)
and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i,
s[i] is the same as or comes before s[i+1] in the alphabet.

Example 1:
Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].

Example 2:
Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.

Example 3:
Input: n = 33
Output: 66045

Constraints:
1 <= n <= 50
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
#include <cfloat>
#include <climits>
#include <map>
#include <set>
#include "extra_data_types.hpp"
using namespace std;
/*
dp[n][k] means the number of strings constructed by at most k different characters.

If k = 1, use only u
If k = 2, use only o,u
If k = 3, use only i,o,u
If k = 4, use only e,i,o,u
If k = 5, use only a,e,i,o,u


Solution 1: Top Down
Time O(nk)
Space O(nk)
where k = 5
    int countVowelStrings(int n) {
        vector<vector<int>>dp(n + 1, vector<int>(6));
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= 5; ++k) {
                dp[i][k] = dp[i][k - 1] + (i > 1 ? dp[i - 1][k] : 1);
            }
        }
        return dp[n][5];
    }
*/
class Solution {
public:
    int countVowelStrings(int n) {
        return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
    }
};