/*
76. Minimum Window Substring

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

        int result = m + 1;
        int left = 0;
        int start = 0;
        int i = 0;
        int required = n;
        while (i <= m and start <= m) {
            if (required > 0) {
                if (i == m) {
                    break;
                }
                count[s[i]] -= 1; // should not use count.find(s[i]) != count.end() to check, cause for cases like bba
                if (count[s[i]] >= 0) {
                    required -= 1;
                }
                i += 1;
            }
            else {
                if (i - start < result) {
                    result = i - start;
                    left = start;
                }
                count[s[start]] += 1;
                if (count[s[start]] > 0) {
                    required += 1;
                }
                start += 1;
            }
        }
        return result == m + 1 ? "" : s.substr(left, result);
    }
};
