/*
201. Bitwise AND of Numbers Range

Given a range [m, n] where 0 <= m <= n <= 2147483647,
return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: [5,7]
Output: 4
Example 2:

Input: [0,1]
Output: 0
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
#include <numeric>
using namespace std;
/*
 The idea is very simple:

 last bit of (odd number & even number) is 0.
 when m != n, There is at least an odd number and an even number, so the last bit position result is 0.
 Move m and n rigth a position.
 Keep doing step 1,2,3 until m equal to n, use a factor to record the iteration time.

 The hardest part of this problem is to find the regular pattern.
 For example, for number 26 to 30
 Their binary form are:
 11010
 11011
 11100
 11101
 11110

 Because we are trying to find bitwise AND,
 so if any bit there are at least one 0 and one 1, it always 0. In this case, it is 11000.
 So we are go to cut all these bit that they are different.
 In this case we cut the right 3 bit.
 I think after understand this, the code is trivial:
 */
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int i = 0;
        for (; m != n; i++) {
            m >>= 1;
            n >>= 1;
        }
        return m << i;
    }
};
