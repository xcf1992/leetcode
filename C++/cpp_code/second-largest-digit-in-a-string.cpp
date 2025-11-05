/*
1796. Second Largest Digit in a String
https://leetcode.com/problems/second-largest-digit-in-a-string/

Given an alphanumeric string s,
return the second largest numerical digit that appears in s,
or -1 if it does not exist.

An alphanumeric string is a string consisting of lowercase English letters and digits.

Example 1:
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
Example 2:
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is no second largest digit.

Constraints:
1 <= s.length <= 500
s consists of only lowercase English letters and/or digits.
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
    int secondHighest(string s) {
        vector<int> digit(10, 0);
        for (char c: s) {
            if (c >= '0' and c
            <=
            '9'
            )
            {
                digit[c - '0'] = 1;
            }
        }

        int result = -2;
        for (int i = 9; i >= 0; --i) {
            if (digit[i] == 0) {
                continue;
            }

            if (result == -2) {
                result = -1;
            } else {
                result = i;
                break;
            }
        }
        return result < 0 ? -1 : result;
    }
};