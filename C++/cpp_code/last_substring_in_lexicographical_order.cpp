/*
1163. Last Substring in Lexicographical Order

Given a string s, return the last substring of s in lexicographical order.

Example 1:
Input: "abab"
Output: "bab"
Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is
"bab".

Example 2:
Input: "leetcode"
Output: "tcode"

Note:
1 <= s.length <= 4 * 10^5
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
#include <stdio.h>
using namespace std;
/*
possible suffix array solution
https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-arrays/tutorial/
*/
class Solution {
public:
    string lastSubstring(string s) {
        int n = s.size();
        if (n <= 1) {
            return s;
        }

        int maxIndex = 0;
        int i = 1;
        while (i < n) {
            if (s[i] > s[maxIndex]) {
                maxIndex = i;
            } else if (s[i] == s[maxIndex]) {
                // We compare them by two pointers i and j
                // i points to one character of cur_str, and j points to max_str
                int j = maxIndex;
                int ori_i = i;
                // If s[i] != s[j] or j == ori_i, then tie is broken
                // Otherwise we keep compare the next character
                int look_back_i = i;
                while (i < n and s[i] == s[j] and j < ori_i) {
                    if (s[i] == s[maxIndex]) {
                        look_back_i = i;
                    }
                    i++;
                    j++;
                }
                // If the max_str is larger than cur_str, then we don't update max_str
                if (j == ori_i or i == n or s[j] > s[i]) {
                    continue;
                }
                // update max_str
                maxIndex = ori_i;
                if (look_back_i != ori_i) {
                    i = look_back_i;  // we need to come back and check from the same character we met in the middle
                }
                continue;
            }
            i += 1;
        }
        return s.substr(maxIndex);
    }
};

class Solution1 {
    // memory limit exceed
public:
    string lastSubstring(string s) {
        int n = s.size();
        if (n <= 1) {
            return s;
        }

        vector<int> subs(26, -1);
        for (int i = 0; i < n; ++i) {
            string sub = s.substr(i);
            if (subs[s[i] - 'a'] == -1 or sub > s.substr(subs[s[i] - 'a'])) {
                subs[s[i] - 'a'] = i;
            }
        }

        string result = "";
        for (int i = 25; i >= 0; i--) {
            if (subs[i] != -1) {
                result = s.substr(subs[i]);
                break;
            }
        }
        return result;
    }
};