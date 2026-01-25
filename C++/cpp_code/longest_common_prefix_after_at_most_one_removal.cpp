/*
https://leetcode.com/problems/longest-common-prefix-after-at-most-one-removal/description/
3460. Longest Common Prefix After at Most One Removal

You are given two strings s and t.

Return the length of the longest common prefix between s and t after removing at most one character from s.

Note: s can be left without any removal.



Example 1:

Input: s = "madxa", t = "madam"

Output: 4

Explanation:

Removing s[3] from s results in "mada", which has a longest common prefix of length 4 with t.

Example 2:

Input: s = "leetcode", t = "eetcode"

Output: 7

Explanation:

Removing s[0] from s results in "eetcode", which matches t.

Example 3:

Input: s = "one", t = "one"

Output: 3

Explanation:

No removal is needed.

Example 4:

Input: s = "a", t = "b"

Output: 0

Explanation:

s and t cannot have a common prefix.



Constraints:

1 <= s.length <= 105
1 <= t.length <= 105
s and t contain only lowercase English letters.
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int longestCommonPrefix(string s, string t) {
        int m = s.size();
        int n = t.size();
        int s_idx = 0;
        int t_idx = 0;
        int rm = 0;
        int rst = 0;
        while (s_idx < m && t_idx < n) {
            if (s[s_idx] == t[t_idx]) {
                s_idx++;
                t_idx++;
                rst += 1;
                continue;
            }

            if (rm != 0) {
                break;
            }

            rm += 1;
            s_idx += 1;
        }
        return rst;
    }
};