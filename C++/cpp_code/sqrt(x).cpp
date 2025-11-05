/*
69. Sqrt(x)
https://leetcode.com/problems/sqrtx/

Implement int sqrt(int x).
Compute and return the square root of x,
where x is guaranteed to be a non-negative integer.

Since the return type is an integer,
the decimal digits are truncated and only the integer part of the result is returned.

Example 1:
Input: 4
Output: 2

Example 2:
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since
             the decimal part is truncated, 2 is returned.
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
public:
    int mySqrt(int x) {
        long long begin = 0;
        long long end = x;
        while (begin < end) {
            long long mid = begin + (end - begin) / 2;
            if (mid * mid == x) {
                return mid;
            } else if (mid * mid < x) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        if (begin * begin > x) {
            return begin - 1;
        }
        return begin;
    }
};