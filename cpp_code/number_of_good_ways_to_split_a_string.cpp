/*
1525. Number of Good Ways to Split a String
https://leetcode.com/problems/number-of-good-ways-to-split-a-string/

You are given a string s,
a split is called good if you can split s into 2 non-empty strings p and q
where its concatenation is equal to s and the number of distinct letters in p and q are the same.

Return the number of good splits you can make in s.

Example 1:
Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good.
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.

Example 2:
Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").

Example 3:
Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.

Example 4:
Input: s = "acbadbaada"
Output: 2

Constraints:
s contains only lowercase English letters.
1 <= s.length <= 10^5
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
using namespace std;
/*
We first count each character (r[ch]), and number of distinct characters (d_r).
These are initial numbers for our right substring (thus, indicated as r).

As we move our split point from left to right,
we "move" the current character to the left substring,
and update count and distinct characters in left and right substrings.

If the number of distict characters is equal, we increment the result.
*/
class Solution {
public:
    int numSplits(string s) {
        vector<int> right(26, 0);
        int diffR = 0;
        for (auto ch : s) {
            right[ch - 'a'] += 1;
            diffR += (right[ch - 'a'] == 1 ? 1 : 0);
        }

        int result = 0;
        int diffL = 0;
        vector<int> left(26, 0);
        for (int i = 0; i < s.size(); ++i) {
            left[s[i] - 'a'] += 1;
            diffL += (left[s[i] - 'a'] == 1 ? 1 : 0);

            right[s[i] - 'a'] -= 1;
            diffR -= (right[s[i] - 'a'] == 0 ? 1 : 0);
            result += diffL == diffR;
        }
        return result;
    }
};
