/*
https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/description/
2749. Minimum Operations to Make the Integer Zero

You are given two integers num1 and num2.

In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.

Return the integer denoting the minimum number of operations needed to make num1 equal to 0.

If it is impossible to make num1 equal to 0, return -1.



Example 1:

Input: num1 = 3, num2 = -2
Output: 3
Explanation: We can make 3 equal to 0 with the following operations:
- We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
- We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
- We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
It can be proven, that 3 is the minimum number of operations that we need to perform.
Example 2:

Input: num1 = 5, num2 = 7
Output: -1
Explanation: It can be proven, that it is impossible to make 5 equal to 0 with the given operation.


Constraints:

1 <= num1 <= 109
-109 <= num2 <= 109
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
using namespace std;
/*
When is x expressible as a sum of exactly k powers of two?

Two simple necessary and sufficient constraints:

x >= 0 (you cannot express a negative number as sum of positive powers of two).

Let bitcount(x) = number of 1 bits in binary representation of x.

The minimum number of powers of two needed to represent x is bitcount(x) (the binary decomposition).

The maximum number of powers you can use to make x is x itself (use x copies of 1 = 2^0).
Therefore x can be written as a sum of exactly k powers of two iff

bitcount(x) <= k <= x.


The reason the lower bound is bitcount(x) is immediate from binary representation.
The reason the upper bound holds is constructive: you can always split a power 2^j into two 2^{j-1}'s repeatedly until
you reach the desired number of terms (and you can keep splitting down to 2^0 = 1), so you can increase the term count
up to x. WalkCCC

(This is the core insight used by standard solutions.)
AlgoMonster
 */
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int k = 1; k <= 60; k++) {
            long long x = num1 - 1LL * num2 * k;
            if (k > x) {
                return -1;
            }
            if (k >= __builtin_popcountll(x)) {
                return k;
            }
        }
        return -1;
    }
};