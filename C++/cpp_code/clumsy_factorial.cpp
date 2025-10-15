/*
1006. Clumsy Factorial

Normally, the factorial of a positive integer n is the product of all positive integers less than or equal to n.
For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.

We instead make a clumsy factorial:
using the integers in decreasing order,
we swap out the multiply operations for a fixed rotation of operations:
multiply (*), divide (/), add (+) and subtract (-) in this order.

For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
However, these operations are still applied using the usual order of operations of arithmetic:
we do all multiplication and division steps before any addition or subtraction steps,
and multiplication and division steps are processed left to right.

Additionally, the division that we use is floor division such that 10 * 9 / 8 equals 11.
This guarantees the result is an integer.

Implement the clumsy function as defined above:
given an integer N, it returns the clumsy factorial of N.

Example 1:
Input: 4
Output: 7
Explanation: 7 = 4 * 3 / 2 + 1

Example 2:
Input: 10
Output: 12
Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1

Note:

1 <= N <= 10000
-2^31 <= answer <= 2^31 - 1  (The answer is guaranteed to fit within a 32-bit integer.)
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
#include <map>
#include <set>
using namespace std;

class Solution {
public:
    int clumsy(int N) {
        if (N == 1 or N == 2) {
            return N;
        }
        if (N == 3) {
            return 3 * 2;
        }

        int result = N * (N - 1) / (N - 2);
        int cur = N - 3;
        while (cur > 0) {
            result += cur;
            cur -= 1;

            if (cur > 0) {
                int temp = cur;
                cur -= 1;
                if (cur > 0) {
                    temp *= cur;
                    cur -= 1;
                }
                if (cur > 0) {
                    temp /= cur;
                    cur -= 1;
                }
                result -= temp;
            }
        }
        return result;
    }
};
