/*
1318. Minimum Flips to Make a OR b Equal to c
https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/

Given 3 positives numbers a, b and c.
Return the minimum flips required in some bits of a and b to make ( a OR b == c ).
(bitwise OR operation).
Flip operation consists of change any single bit 1 to 0
or change the bit 0 to 1 in their binary representation.

Example 1:
Input: a = 2, b = 6, c = 5
Output: 3
Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)

Example 2:
Input: a = 4, b = 2, c = 7
Output: 1

Example 3:
Input: a = 1, b = 2, c = 3
Output: 0

Constraints:
1 <= a <= 10^9
1 <= b <= 10^9
1 <= c <= 10^9
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
#include "extra_data_types.hpp"
using namespace std;
// put | and & bit operation into () before compare
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int result = 0;
        while (a != 0 or b != 0 or c != 0) {
            int d1 = (a & 1);
            a >>= 1;
            int d2 = (b & 1);
            b >>= 1;
            int d3 = (c & 1);
            c >>= 1;
            if ((d1 | d2) == d3) {
                continue;
            }
            if (d3 == 1) {
                result += 1;
            }
            else {
                result += d1 + d2;
            }
        }
        return result;
    }
};
