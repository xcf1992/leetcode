/*
1624. Largest Substring Between Two Equal Characters
https://leetcode.com/problems/largest-substring-between-two-equal-characters/

Given a string s, return the length of the longest substring between two equal characters,
excluding the two characters. If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "aa"
Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.

Example 2:
Input: s = "abca"
Output: 2
Explanation: The optimal substring here is "bc".

Example 3:
Input: s = "cbzxy"
Output: -1
Explanation: There are no characters that appear twice in s.

Example 4:
Input: s = "cabbac"
Output: 4
Explanation: The optimal substring here is "abba". Other non-optimal substrings include "bb" and "".

Constraints:
1 <= s.length <= 300
s contains only lowercase English letters.
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

using namespace std;

class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int result = -1;
        vector<int> last(26, -1);
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (last[c - 'a'] == -1) {
                last[c - 'a'] = i;
                continue;
            }
            result = max(result, i - last[c - 'a'] - 1);
        }
        return result;
    }
};
