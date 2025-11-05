/*
1814. Count Nice Pairs in an Array
https://leetcode.com/problems/count-nice-pairs-in-an-array/

You are given an array nums that consists of non-negative integers.
Let us define rev(x) as the reverse of the non-negative integer x.
For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j)
is nice if it satisfies all of the following conditions:
0 <= i < j < nums.length
nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
Return the number of nice pairs of indices. Since that number can be too large,
return it modulo 109 + 7.

Example 1:
Input: nums = [42,11,1,97]
Output: 2
Explanation: The two pairs are:
 - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
 - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
Example 2:
Input: nums = [13,10,35,24,76]
Output: 4

Constraints:
1 <= nums.length <= 105
0 <= nums[i] <= 109
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
A[i] + rev(A[j]) == A[j] + rev(A[i])
A[i] - rev(A[i]) == A[j] - rev(A[j])
B[i] = A[i] - rev(A[i])

Then it becomes an easy question that,
how many pairs in B with B[i] == B[j]

Complexity
Time O(nloga)
Space O(n)
*/
class Solution {
public:
    int countNicePairs(vector<int> &A) {
        int res = 0, mod = 1e9 + 7;
        unordered_map<int, int> count;
        for (int &a: A)
            res = (res + count[a - rev(a)]++) % mod;
        return res;
    }

    int rev(int a) {
        int b = 0;
        while (a > 0) {
            b = b * 10 + (a % 10);
            a /= 10;
        }
        return b;
    }
};