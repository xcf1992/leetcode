/*
7. Reverse Integer
https://leetcode.com/problems/reverse-integer/

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:
Input: 123
Output: 321

Example 2:
Input: -123
Output: -321

Example 3:
Input: 120
Output: 21

Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
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
public:
    int reverse(int x) {
        long long temp = x;
        bool negative = false;
        if (temp < 0) {
            negative = true;
            temp = 0 - temp;
        }

        long long reverse = 0;
        while (temp != 0) {
            reverse = reverse * 10 + temp % 10;
            if (reverse > INT_MAX) {
                return 0;
            }
            temp = temp / 10;
        }

        if (negative) {
            return 0 - reverse;
        }
        return reverse;
    }
};