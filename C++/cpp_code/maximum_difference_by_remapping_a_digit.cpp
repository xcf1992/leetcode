/*
https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/description/
2566. Maximum Difference by Remapping a Digit

You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another
digit.

Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.

Notes:

When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
Bob can remap a digit to itself, in which case num does not change.
Bob can remap different digits for obtaining minimum and maximum values respectively.
The resulting number after remapping can contain leading zeroes.


Example 1:

Input: num = 11891
Output: 99009
Explanation:
To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
The difference between these two numbers is 99009.
Example 2:

Input: num = 90
Output: 99
Explanation:
The maximum value that can be returned by the function is 99 (if 0 is replaced by 9) and the minimum value that can be
returned by the function is 0 (if 9 is replaced by 0). Thus, we return 99.


Constraints:

1 <= num <= 108
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
#include <set>
using namespace std;

class Solution {
    int string_to_number(string str) {
        int n = str.size();
        int rst = 0;
        int i = 0;
        while (i < n && str[i] == '0') {
            i += 1;
        }

        while (i < n) {
            rst = rst * 10 + (str[i] - '0');
            i += 1;
        }
        return rst;
    }

public:
    int minMaxDifference(int num) {
        string num_str = to_string(num);
        int n = num_str.size();
        string min_val = num_str;
        char min_c = min_val[0];
        for (int i = 0; i < n; i++) {
            if (min_val[i] == min_c) {
                min_val[i] = '0';
            }
        }

        string max_val = num_str;
        char max_c = max_val[0];
        for (int i = 0; i < n; i++) {
            if (max_val[i] != '9') {
                max_c = max_val[i];
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (max_val[i] == max_c) {
                max_val[i] = '9';
            }
        }
        return string_to_number(max_val) - string_to_number(min_val);
    }
};