/*
1234. Replace the Substring for Balanced String
https://leetcode.com/problems/replace-the-substring-for-balanced-string/

You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.
A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.

Return the minimum length of the substring
that can be replaced with any other string of the same length to make the original string s balanced.
Return 0 if the string is already balanced.

Example 1:
Input: s = "QWER"
Output: 0
Explanation: s is already balanced.

Example 2:
Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.

Example 3:
Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER".

Example 4:
Input: s = "QQQQ"
Output: 3
Explanation: We can replace the last 3 'Q' to make s = "QWER".

Constraints:
1 <= s.length <= 10^5
s.length is a multiple of 4
s contains only 'Q', 'W', 'E' and 'R'.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    int balancedString(string s) {
        int n = s.size();
        unordered_map<char, int> count;
        for (char c : s) {
            count[c] += 1;
        }

        int needed = 0;
        for (auto& it : count) {
            it.second = max(0, it.second - n / 4);
            needed += it.second;
        }
        if (needed == 0) {
            return 0;
        }

        int result = n;
        int left = 0;
        int right = 0;
        while (right < n) {
            count[s[right]] -= 1;
            if (count[s[right]] >= 0) {
                needed -= 1;
            }
            right += 1;

            if (needed > 0) {
                continue;
            }

            while (needed == 0) {
                count[s[left]] += 1;
                if (count[s[left]] > 0) {
                    needed += 1;
                }
                left += 1;
            }
            result = min(result, right - left + 1);
        }
        return result;
    }
};
