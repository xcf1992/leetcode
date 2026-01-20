/*
https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/description/
3314. Construct the Minimum Bitwise Array I
You are given an array nums consisting of n prime integers.

You need to construct an array ans of length n, such that, for each index i, the bitwise OR of ans[i] and ans[i] + 1 is
equal to nums[i], i.e. ans[i] OR (ans[i] + 1) == nums[i].

Additionally, you must minimize each value of ans[i] in the resulting array.

If it is not possible to find such a value for ans[i] that satisfies the condition, then set ans[i] = -1.



Example 1:

Input: nums = [2,3,5,7]

Output: [-1,1,4,3]

Explanation:

For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.
Example 2:

Input: nums = [11,13,31]

Output: [9,12,15]

Explanation:

For i = 0, the smallest ans[0] that satisfies ans[0] OR (ans[0] + 1) = 11 is 9, because 9 OR (9 + 1) = 11.
For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 13 is 12, because 12 OR (12 + 1) = 13.
For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 31 is 15, because 15 OR (15 + 1) = 31.


Constraints:

1 <= nums.length <= 100
2 <= nums[i] <= 1000
nums[i] is a prime number.
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
#include <set>
#include <numeric>
using namespace std;
/*
if num is even, then it is not possible to find the answer
Recall: Adding 1 to a number flips the trailing zeros to the rightmost set bit.
23 : 1 0 1 1 1
+1
24 : 1 1 0 0 0

x = 71 :    1 0 0 0 1 1 1
x + 1 = 72: 1 0 0 1 0 0 0
n =     79: 1 0 0 1 1 1 1

Notice that x and n differ at exactly one bit position: the rightmost 0 bit in x (at position 3).

In terms of n, it is exactly its leftmost suffix ones.

THEREFORE:
To find x from n, we need to FLIP the leftmost one in the trailing ones of n.

Instead of directly finding that zero, we invert the bits ∼n, then:

Recall: The special bit trick to find the rightmost set bit. q & (q - 1)
*/
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> rst;
        for (int val : nums) {
            if (val & 1) {
                int z = ((val + 1) & ~val) >> 1;
                rst.push_back(val & ~z);
            } else {
                rst.push_back(-1);
            }
        }
        return rst;
    }
};