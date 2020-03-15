/*
1330. Reverse Subarray To Maximize Array Value
https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/

You are given an integer array nums.
The value of this array is defined as the sum of |nums[i]-nums[i+1]|
for all 0 <= i < nums.length-1.

You are allowed to select any subarray of the given array and reverse it.
You can perform this operation only once.
Find maximum possible value of the final array.

Example 1:
Input: nums = [2,3,1,5,4]
Output: 10
Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.

Example 2:
Input: nums = [2,4,9,24,2,1,10]
Output: 68

Constraints:
1 <= nums.length <= 3*10^4
-10^5 <= nums[i] <= 10^5
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
#include "extra_data_types.hpp"
using namespace std;
/*
What's the score after reversing a sub-array [L, R] ?
It's the score without reversing it + abs(a[R] - a[L-1]) + abs(a[L] - a[R+1]) - abs(a[L] - a[L-1]) - abs(a[R] - a[R+1])
How to maximize that formula given that abs(x - y) = max(x - y, y - x) ?
This can be written as max(max(a[R] - a[L - 1], a[L - 1] - a[R]) + max(a[R + 1] - a[L], a[L] - a[R + 1]) - value(L) - value(R + 1)) over all L < R where value(i) = abs(a[i] - a[i-1])
This can be divided into 4 cases.

-=-=-=-=-=-=-=-=

total calculate the total sum of |A[i] - A[j]|.
res record the value the we can improve.

Assume the current pair is (a,b) = (A[i], A[i+1]).

If we reverse all element from A[0] to A[i],
we will improve abs(A[0] - b) - abs(a - b)

If we reverse all element from A[i+1] to A[n-1],
we will improve abs(A[n - 1] - a) - abs(a - b)

As we iterate the whole array,
We also record the maximum pair and the minimum pair.
We can break these two pair and reverse all element in the middle.
This will improve (max2 - min2) * 2

-=-=

Here is my attempt to explain the core logic of the algorithm i.e. trying to find the optimal subarray whose edges are not 0 or length - 1 and reversing which gives us the largest total sum (or gives maximum bump to the default sum).

First, reversing any non-edgy subarray will result in modifying 2 continuous pairs e.g if array is a,b,...,c,d, reversing {b...c} results in a,c,...,b,d, only pairs (a,b) and (c,d) are impacted.

Now, if the 2 pairs are non-overlapping, (max of one pair < min of other pair) then they are not utilizing the range which is between them in the sum e.g. given a < b < c < d , then the range not used is (c - b). So, greater the difference between the range, greater opportunity we are missing to add it to the overall sum. So first we have to find out the 2 pairs with maximal difference.

Now, after finding the pairs, no matter in what way you make them overlapping, you will always get benefit of 2*(c - b). To see how, lets arrange the 4 numbers in a number line with a < b < c < d. The maximum sum we can get out of them is (b - a) + 2*(c - b) + (d - c). Lets take examples of 2 ways we can make the range overlapping
a. Swapping c and b: Since c > b ,and earlier contribution was (b - a), we have changed the contribution to (c - a) i.e (c - b) more. Similarly, other pair has also increased the contribution by (c - b) (as we have reduced the subtracting value). So total 2*(c - b)
b. Suppose the numbers are b > a < c < d where (c,d are also less than b). Swapping c and a means we have reduced the total contribution of first pair to (c - b) but the contribution of second pair now is (d - c) + (b - a) + (c - b) (as now a is the smallest of all).
So no matter how the 2 pairs are arranged in the number line if you make them overlap by swapping any element of the 2 pairs, the contribution will always be increased by 2*(max of min pair - min of max pair).
*/
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        int total = 0;
        int res = 0;
        int minNum = INT_MAX;
        int maxNum = INT_MIN;
        for (int i = 0; i < n - 1; ++i) {
            int a = nums[i];
            int b = nums[i + 1];
            total += abs(a - b);
            res = max(res, abs(nums[0] - b) - abs(a - b));
            res = max(res, abs(nums[n - 1] - a) - abs(a - b));
            minNum = min(minNum, max(a, b));
            maxNum = max(maxNum, min(a, b));
        }
        return total + max(res, (maxNum - minNum) * 2);
    }
};
