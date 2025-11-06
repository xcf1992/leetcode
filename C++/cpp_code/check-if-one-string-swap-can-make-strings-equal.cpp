/*
1790. Check if One String Swap Can Make Strings Equal
https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/

You are given two strings s1 and s2 of equal length.
A string swap is an operation where you choose two indices in a string
(not necessarily different) and swap the characters at these indices.

Return true if it is possible to make both strings equal by performing
at most one string swap on exactly one of the strings.
Otherwise, return false.

Example 1:
Input: s1 = "bank", s2 = "kanb"
Output: true
Explanation: For example, swap the first character with the last character of s2 to make "bank".
Example 2:
Input: s1 = "attack", s2 = "defend"
Output: false
Explanation: It is impossible to make them equal with one string swap.
Example 3:
Input: s1 = "kelb", s2 = "kelb"
Output: true
Explanation: The two strings are already equal, so no string swap operation is required.
Example 4:
Input: s1 = "abcd", s2 = "dcba"
Output: false

Constraints:
1 <= s1.length, s2.length <= 100
s1.length == s2.length
s1 and s2 consist of only lowercase English letters.
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
using namespace std;

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> cnt;
        // find the number of diff chars
        for (int i = 0; i < s1.size() && cnt.size() < 3; i++) {
            if (s1[i] != s2[i]) {
                cnt.push_back(i);
            }
        }
        // when the chars are exactly the same or there is only one pair of diff chars, check if swapping makes them
        // equal then return true
        return (cnt.size() == 0) || ((cnt.size() == 2) && (s1[cnt[0]] == s2[cnt[1]] || s1[cnt[1]] == s2[cnt[0]]));
    }
};
