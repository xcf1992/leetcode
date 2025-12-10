/*
1611. Minimum One Bit Operations to Make Integers Zero
https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/

Given an integer n, you must transform it into 0 using the following operations any number of times:
Change the rightmost (0th) bit in the binary representation of n.
Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are
set to 0. Return the minimum number of operations to transform n into 0.

Example 1:
Input: n = 0
Output: 0

Example 2:
Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.

Example 3:
Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.

Example 4:
Input: n = 9
Output: 14

Example 5:
Input: n = 333
Output: 393

Constraints:
0 <= n <= 109
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
#include <cfloat>
#include <climits>
#include <map>

using namespace std;
/*
Intuition
For 1XXXXXXX,
we need to transfer it
1XXXXXXX -> ... -> 11000000 -> 1000000 -> ... -> 0


Observation 1
The two operations are undo-able.
If a -> b needs k operation,
b -> a also needs k operation.


Observation 2
1 -> 0 needs 1 operation,
2 -> 0 needs 3 operations,
4 -> 0 needs 7 operations,
2^k needs 2^(k+1)-1 operations.

This can be easily proved.


Solution 1: Recursion
1XXXXXX -> 1100000 -> 100000 -> 0

1XXXXXX -> 1100000 needs minimumOneBitOperations(1XXXXXX ^ 1100000),
because it needs same operations 1XXXXXX ^ 1100000 -> 1100000 ^ 1100000 = 0.

1100000 -> 100000 needs 1 operation.
100000 -> 0, where 100000 is 2^k, needs 2^(k+1) - 1 operations.

In total,
f(n) = f((b >> 1) ^ b ^ n) + 1 + b - 1,
where b is the maximum power of 2 that small or equals to n.

Time O(logn)
Space O(logn)
*/
class Solution {
public:
    int minimumOneBitOperations(int n, int res = 0) {
        if (n == 0)
            return res;
        int b = 1;
        while ((b << 1) <= n)
            b = b << 1;
        return minimumOneBitOperations((b >> 1) ^ b ^ n, res + b);
    }
};