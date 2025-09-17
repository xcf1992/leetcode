/*
1703. Minimum Adjacent Swaps for K Consecutive Ones
https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/

You are given an integer array, nums, and an integer k.
nums comprises of only 0's and 1's. In one move,
 you can choose two adjacent indices and swap their values.

Return the minimum number of moves required so that nums has k consecutive 1's.

Example 1:
Input: nums = [1,0,0,1,0,1], k = 2
Output: 1
Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
Example 2:
Input: nums = [1,0,0,0,0,0,1,1], k = 3
Output: 5
Explanation: In 5 moves, the leftmost 1 can be shifted right until nums = [0,0,0,0,0,1,1,1].
Example 3:
Input: nums = [1,1,0,1], k = 2
Output: 0
Explanation: nums already has 2 consecutive 1's.

Constraints:
1 <= nums.length <= 105
nums[i] is 0 or 1.
1 <= k <= sum(nums)
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
Find all index of nums[i] if nums[i] == 1.
Now the problem changes to,
find k consecute element in A,
that has minimum distance to their median sequence.
To solve this, we need to use the prefix sum of A,
which is B in this solution.

Niubi solution ! Here is my attempt to elaborate on the Java solution:
Assuming we have no problem understanding the first 7 lines of code, with indices of all '1's stored in the array A.

Now the subproblem here is:
Given an integer array, how to compute the sum of the absolute difference between each element and the median element of the array?

For instance, if the array A is [1, 2, 3, 4, 5] whose median element is 3, a naive approach would be summing up all absolute differences:
(3 - 1) + (3 - 2) + (3 - 3) + (4 - 3) + (5 - 3), which has O(k) time complexity, with k being the length of A.
The trick introduced in

for (int i = 0; i < A.size(); ++i)
    B.add(B.get(i) + A.get(i));
for (int i = 0; i <  A.size() - k + 1; ++i)
    res = Math.min(res, B.get(i + k) - B.get(k / 2 + i) - B.get((k + 1) / 2 + i) + B.get(i));
is by precomputing the prefix sum to efficiently retrieve the desired result in O(1) time !

It is easier to understand this trick if we reorganize the formula of the "naive" approach in this way:
(3 - 1) + (3 - 2) + (3 - 3) + (4 - 3) + (5 - 3) <=> (3 + 4 + 5) - (1 + 2 + 3), that is range_sum[k/2, k - 1] - range_sum[0, (k - 1)/2], where range_sum(i, j) represents the sum of the elements between indices i and j, inclusive. The range_sum can be computed using prefix sum in O(1) time. If you have difficulty understanding this, please check out leetcode problem #303 and https://en.wikipedia.org/wiki/Prefix_sum.
And it also applies to the arrays with even numbers of elements, i.e. when k is even. For example:
the formula for [1, 2, 3, 4, 5, 6] is (4 - 1) + (4 - 2) + (4 - 3) + (4 - 4) + (5 - 4) + (6 - 4) and can be simplified to (4 + 5 + 6) - (1 + 2 + 3), with 4 being the selected median element. Then we can use this trick to quickly find the minimum sum of absolute differences for each sliding window.

However, back to the problem, it is not done yet!

Note that in the index array A: [1, 2, 3, 4, 5], although the absolute difference between 2 and 3 is 1, the '1's located at these two indices are already next to each other, so we do not have to move anything;
On the other hand, the '1' at index 1 is two steps away from the '1' at index 3, but there is already a '1' between them (at index 2), so again, we do not need to move anything.
Based on the above observations, each positive absolute index difference (abs_diff) needs to be calibrated first with:

abs_diff[i] -= 1; // based on observation 1
And secondly,

abs_diff[i] -= (abs(k / 2 - i) - 1)); // based on observation 2
And they can be combined as

abs(k / 2 - i)
where, i = 0, 1, 2, ..., k - 1. If you expand all calibration items abs(k / 2 - i) from i = 0 to i = k - 1 you will have

[k / 2, k / 2 - 1, ... 1, 0, 1, ..., (k + 1) / 2 - 1]
where the last element abs(k / 2 - (k - 1)) has been simplified to (k + 1) / 2 - 1.
Here I did not come up with a systematic approach to simplify this formula. However, we can still prove that it is equivalent to

(k / 2) * ((k + 1) / 2)
when k is a positive integer.

If k is odd, k / 2 = (k + 1) / 2 - 1, therefore the abs_diff array is symmetric and the left half (elements to the left of 0) and right half (elements to the right of 0) can be both computed as,
k / 2 * (k / 2 + 1) * 1 / 2
So the sum is k / 2 * (k / 2 + 1) = k / 2 * ((k + 1) / 2) when k is odd;
2. if k is even, we let t = k + 1, then t is odd, and the array becomes

[(t - 1) / 2, (t - 1) / 2 - 1, ... 1, 0, 1, ..., t / 2 - 1]
and can be further simplified to

[t / 2, t / 2 - 1, ... 1, 0, 1, ..., t / 2 - 1]
We can observe that the left half has one more element (t / 2) compared to the right half. Using the formula we just derived, the sum can be expressed as,

(1 + t / 2 - 1) * (t / 2 - 1) * 1 / 2 * 2 + t / 2 = t / 2 * t / 2 = ((k + 1) / 2) * ((k + 1) / 2)
where, ((k + 1) / 2) * ((k + 1) / 2) = k / 2 * ((k + 1) / 2) when k is even.

Finally, subtract the sum of the abs_diff array from res will give us the result.
*/
class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        vector<long> A, B(1);
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i]) {
                A.push_back(i);
            }
        }

        long n = A.size(), res = 2e9;
        for (int i = 0; i < n; ++i) {
            B.push_back(B[i] + A[i]);
        }

        for (int i = 0; i < n - k + 1; ++i) {
            res = min(res, B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i]);
        }
        res -= (k / 2) * ((k + 1) / 2);
        return res;
    }
};
