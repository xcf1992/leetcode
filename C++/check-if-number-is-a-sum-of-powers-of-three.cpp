/*
1780. Check if Number is a Sum of Powers of Three
https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/

Given an integer n,
return true if it is possible to represent n as the sum of distinct powers of three.
Otherwise, return false.
An integer y is a power of three
if there exists an integer x such that y == 3x.

Example 1:
Input: n = 12
Output: true
Explanation: 12 = 31 + 32
Example 2:
Input: n = 91
Output: true
Explanation: 91 = 30 + 32 + 34
Example 3:
Input: n = 21
Output: false

Constraints:
1 <= n <= 107
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
Relatively simple problem -
think how you would convert a number to binary (ie: base 2)
then do the same to convert it to base 3 -
returning false as soon as we get a2 digit in our number.

If we managed to reduce the original number to 0,
then it was completely made of powers of 3 (ie: in base 3 it would just be made of 0 and 1s).
*/
class Solution {
public:
    bool checkPowersOfThree(int n) {
        // grinding n down by powers of 3
        while (n) {
            if (n % 3 == 2) {
                return false;
            }
            n /= 3;
        }
        return true;
    }
};
