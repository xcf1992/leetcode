/*
1717. Maximum Score From Removing Substrings
https://leetcode.com/problems/maximum-score-from-removing-substrings/

You are given a string s and two integers x and y.
You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

Example 1:
Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.
Example 2:
Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20

Constraints:
1 <= s.length <= 105
1 <= x, y <= 104
s consists of lowercase English letters.
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
    int remove(string &s, string r, int x) {
        int i = 0, ans = 0; // `i` is write pointer, `j` is read pointer.
        for (int j = 0; j < s.size(); ++j) {
            s[i++] = s[j];
            if (i > 1 && s[i - 2] == r[0] && s[i - 1] == r[1]) {
                i -= 2, ans += x; // We keep removing pattern string `r` when `r` shows up in the end of written part.
            }
        }
        s.resize(i);
        return ans;
    }

public:
    int maximumGain(string s, int x, int y) {
        string a = "ab", b = "ba";
        if (x < y) {
            swap(a, b), swap(x, y);
        }
        return remove(s, a, x) + remove(s, b, y);
    }
};