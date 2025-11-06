/*
76. Minimum Window Substring
https://leetcode.com/problems/minimum-window-substring/

Given a string S and a string T,
find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

Note:
If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        if (m == 0 or n == 0 or n > m) {
            return "";
        }

        unordered_map<char, int> count;
        for (char c : t) {
            count[c] += 1;
        }

        int minLen = m + 1;
        int left = 0;
        int start = 0;
        int end = 0;
        int required = n;
        while (end <= m and start <= m) {
            if (required > 0) {
                if (end == m) {
                    break;
                }

                count[s[end]] -=
                        1;  // should not use count.find(s[i]) != count.end() to check, cause for cases like bba
                if (count[s[end]] >= 0) {
                    required -= 1;
                }
                end += 1;
            } else {
                if (end - start < minLen) {
                    minLen = end - start;
                    left = start;
                }

                count[s[start]] += 1;
                if (count[s[start]] > 0) {
                    required += 1;
                }
                start += 1;
            }
        }
        return minLen == m + 1 ? "" : s.substr(left, minLen);
    }
};