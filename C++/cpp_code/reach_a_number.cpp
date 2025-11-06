/*
754. Reach a Number

You are standing at position 0 on an infinite number line.
There is a goal at position target.

On each move, you can either go left or right.
During the n-th move (starting from 1), you take n steps.

Return the minimum number of steps required to reach the destination.

Example 1:
Input: target = 3
Output: 2
Explanation:
On the first move we step from 0 to 1.
On the second step we step from 1 to 3.

Example 2:
Input: target = 2
Output: 3
Explanation:
On the first move we step from 0 to 1.
On the second move we step  from 1 to -1.
On the third move we step from -1 to 2.

Note:
target will be a non-zero integer in the range [-10^9, 10^9].
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

class Solution {
public:
    int reachNumber(int target) {
        if (target < 0) {
            target = 0 - target;
        }
        int n = 1;
        int cur = 0;
        while (cur < target) {
            cur += n;
            n += 1;
        }
        if (target == cur) {
            return n - 1;
        }
        /*
        * If S > target, we need to change some number signs.
        * If delta = S - target is even, then we can always find a subset of {1, 2, ..., k} equal to delta / 2
        * and switch the signs, so the answer is k.
        * (This depends on T = delta / 2 being at most S.)
        * [The proof is simple: either T <= k and we choose it,
        * or we choose k in our subset and try to solve the same instance of the problem for T -= k
        * and the set {1, 2, ..., k-1}.]

        * Otherwise, if delta is odd, we can't do it,
        * as every sign change from positive to negative changes the sum by an even number.
        * So let's consider a candidate answer of k+1, which changes delta by k+1.
        * If this is odd, then delta will be even and we can have an answer of k+1.
        * Otherwise, delta will be odd, and we will have an answer of k+2.
        */
        while ((cur - target) % 2 != 0) {
            cur += n;
            n += 1;
        }
        return n - 1;
    }
};