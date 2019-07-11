/*
371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1

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
    int getSum(int a, int b) {
        long long carry; // 64-bit
        while (b != 0) {
            carry = a & b;
            a = a ^ b;
            b = ((carry & 0xffffffff) << 1); // limited to 32 bits
        }
        return a;
    }
};
