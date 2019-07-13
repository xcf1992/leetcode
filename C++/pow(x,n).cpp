/*
50. Pow(x, n)
Implement pow(x, n), which calculates x raised to the power n (xn).

Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
Note:

-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−231, 231 − 1]
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
    double calculate(double x, long long n) {
        double result = 1.0;
        while (n > 0) {
            if (n & 1) {
                result *= x;
            }
            x *= x;
            n = n >> 1;
        }
        return result;
    }
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            return (double) 1.0 / calculate(x, (long long)0 - n);
        }
        return calculate(x, n);
    }
};