/*
29. Divide Two Integers

Given two integers dividend and divisor,
divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.
The integer division should truncate toward zero.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3

Example 2:
Input: dividend = 7, divisor = -3
Output: -2

Note:
Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment
which could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        if (divisor == 1) {
            return dividend;
        }
        if (divisor == -1) {
            long result = 0 - (long)dividend;
            return result > INT_MAX ? INT_MAX : result;
        }

        long a = labs(dividend);
        long b = labs(divisor);
        long result = 0;
        while (a >= b) {
            long count = 1;
            long temp = b;
            while (temp <= a) {
                a -= temp;
                result += count;
                temp = temp << 1;
                count = count << 1;
            }
        }

        if (dividend > 0 ^ divisor > 0) {
            return 0 - result;
        }
        return result;
    }
};
