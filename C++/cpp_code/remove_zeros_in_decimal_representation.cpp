/*
https://leetcode.com/problems/remove-zeros-in-decimal-representation/description/
3726. Remove Zeros in Decimal Representation

You are given a positive integer n.

Return the integer obtained by removing all zeros from the decimal representation of n.



Example 1:

Input: n = 1020030

Output: 123

Explanation:

After removing all zeros from 1020030, we get 123.

Example 2:

Input: n = 1

Output: 1

Explanation:

1 has no zero in its decimal representation. Therefore, the answer is 1.



Constraints:

1 <= n <= 1015
*/
#include <iostream>
#include <sstream>
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
    long long removeZeros(long long n) {
        long long result = 0;
        long long factor = 1;
        while (n != 0) {
            int digit = n % 10;
            if (digit != 0) {
                result += digit * factor;
                factor *= 10;
            }
            n /= 10;
        }
        return result;
    }
};