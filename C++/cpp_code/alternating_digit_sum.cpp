/*
https://leetcode.com/problems/alternating-digit-sum/description/
2544. Alternating Digit Sum

You are given a positive integer n. Each digit of n has a sign according to the following rules:

The most significant digit is assigned a positive sign.
Each other digit has an opposite sign to its adjacent digits.
Return the sum of all digits with their corresponding sign.



Example 1:

Input: n = 521
Output: 4
Explanation: (+5) + (-2) + (+1) = 4.
Example 2:

Input: n = 111
Output: 1
Explanation: (+1) + (-1) + (+1) = 1.
Example 3:

Input: n = 886996
Output: 0
Explanation: (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.


Constraints:

1 <= n <= 109
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
#include <climits>

using namespace std;

class Solution {
public:
    int alternateDigitSum(int n) {
        stack<int> digits;
        while (n != 0) {
            digits.push(n % 10);
            n = n / 10;
        }

        int rst = 0;
        int positive = 1;
        while (!digits.empty()) {
            rst += digits.top() * positive;
            digits.pop();
            positive *= -1;
        }
        return rst;
    }
};