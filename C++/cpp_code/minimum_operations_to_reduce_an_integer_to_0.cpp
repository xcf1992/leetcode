/*
https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/description/
2571. Minimum Operations to Reduce an Integer to 0

You are given a positive integer n, you can do the following operation any number of times:

Add or subtract a power of 2 from n.
Return the minimum number of operations to make n equal to 0.

A number x is power of 2 if x == 2i where i >= 0.



Example 1:

Input: n = 39
Output: 3
Explanation: We can do the following operations:
- Add 20 = 1 to n, so now n = 40.
- Subtract 23 = 8 from n, so now n = 32.
- Subtract 25 = 32 from n, so now n = 0.
It can be shown that 3 is the minimum number of operations we need to make n equal to 0.
Example 2:

Input: n = 54
Output: 3
Explanation: We can do the following operations:
- Add 21 = 2 to n, so now n = 56.
- Add 23 = 8 to n, so now n = 64.
- Subtract 26 = 64 from n, so now n = 0.
So the minimum number of operations is 3.


Constraints:

1 <= n <= 105
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
#include <map>
using namespace std;
/*
Take a look at the binary of n:

If there is an alone 1, like ..00001,
it takes at leat one operation to remove.
and we can remove it in one operation.
So we do res++ and n >>= 2,
remove two last bits.

If there are multiple 1s, like ..0000111,
we can't remove them in one single operation,
so it takes at least two operation to remove,
For example of ..0000111
we can add 1 and then remove 1000.
So we do n++ and remove the last bit 0.


Explanation
By this stratagy in intuition,
we only need to take care of the the continuous 1 in binary of n.
If it's single 1, res += 1
If it's multiple 1s, res += 2
 */
class Solution {
public:
    int minOperations(int n) {
        int rst = 0;
        while (n != 0) {
            int temp = n;
            while (temp != 0 && (temp & 1) == 0) {
                temp >>= 1;
            }

            int cnt = 0;
            while (temp != 0 && (temp & 1) != 0) {
                cnt += 1;
                temp >>= 1;
            }

            if (cnt == 1) {
                rst += 1;
            } else {
                rst += 1;
                temp += 1;
            }
            n = temp;
        }
        return rst;
    }
};