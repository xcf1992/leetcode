/*
1247. Minimum Swaps to Make Strings Equal
https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/

You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only.
Your task is to make these two strings equal to each other.
You can swap any two characters that belong to different strings,
which means: swap s1[i] and s2[j].

Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.

Example 1:
Input: s1 = "xx", s2 = "yy"
Output: 1
Explanation:
Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".

Example 2:
Input: s1 = "xy", s2 = "yx"
Output: 2
Explanation:
Swap s1[0] and s2[0], s1 = "yy", s2 = "xx".
Swap s1[0] and s2[1], s1 = "xy", s2 = "xy".
Note that you can't swap s1[0] and s1[1] to make s1 equal to "yx", cause we can only swap chars in different strings.

Example 3:
Input: s1 = "xx", s2 = "xy"
Output: -1

Example 4:
Input: s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx"
Output: 4

Constraints:
1 <= s1.length, s2.length <= 1000
s1, s2 only contain 'x' or 'y'.
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        if (n1 != n2) {
            return -1;
        }

        int countX = 0;
        int countY = 0;
        for (int i = 0; i < n1; ++i) {
            if (s1[i] != s2[i]) {
                countX += s1[i] == 'x' ? 1 : 0;
                countY += s1[i] == 'y' ? 1 : 0;
            }
        }

        int result = countX / 2 + countY / 2;
        countX %= 2;
        countY %= 2;
        if (countX == 0) {
            return countY == 0 ? result : -1;
        }
        return countY == 0 ? -1 : result + 2;
    }
};