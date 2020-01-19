/*
1067. Digit Count in Range

Given an integer d between 0 and 9,
and two positive integers low and high as lower and upper bounds, respectively.
Return the number of times that d occurs as a digit in all integers between low and high,
including the bounds low and high.

Example 1:
Input: d = 1, low = 1, high = 13
Output: 6
Explanation:
The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.

Example 2:
Input: d = 3, low = 100, high = 250
Output: 35
Explanation:
The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.

Note:
0 <= d <= 9
1 <= low <= high <= 2×10^8
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

class Solution {
private:
    int getCount(int d, int bound) { // compute number of times digit c appears in from 0 to bound inclusively.
        int result = 0;
        for (long i = 1; i <= bound; i *= 10) {
            long divisor = i * 10;
            result += (bound / divisor) * i;
            /*
            * when d == 0, when analyzing the remainder,
            * we need avoid taking numbers with "heading zero"
            * like 0xxxx into the total count.
            */
            if (d == 0) {
                result -= i;
            }

            int remainder = bound % divisor;
            if (remainder >= d * i) {
                result += min(i, remainder - d * i + 1);
            }
        }
        return result;
    }
public:
    int digitsCount(int d, int low, int high) {
        if (d < 0 or high < 0) {
            return 0;
        }
        return getCount(d, high) - getCount(d, low - 1);
    }
};
