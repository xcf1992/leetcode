/*
https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/description/
3420. Count Non-Decreasing Subarrays After K Operations

You are given an array nums of n integers and an integer k.

For each subarray of nums, you can apply up to k operations on it. In each operation, you increment any element of the
subarray by 1.

Note that each subarray is considered independently, meaning changes made to one subarray do not persist to another.

Return the number of subarrays that you can make non-decreasing ​​​​​after performing at most k operations.

An array is said to be non-decreasing if each element is greater than or equal to its previous element, if it exists.



Example 1:

Input: nums = [6,3,1,2,4,4], k = 7

Output: 17

Explanation:

Out of all 21 possible subarrays of nums, only the subarrays [6, 3, 1], [6, 3, 1, 2], [6, 3, 1, 2, 4] and [6, 3, 1, 2,
4, 4] cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays
is 21 - 4 = 17.

Example 2:

Input: nums = [6,3,1,3,6], k = 4

Output: 12

Explanation:

The subarray [3, 1, 3, 6] along with all subarrays of nums with three or fewer elements, except [6, 3, 1], can be made
non-decreasing after k operations. There are 5 subarrays of a single element, 4 subarrays of two elements, and 2
subarrays of three elements except [6, 3, 1], so there are 1 + 5 + 4 + 2 = 12 subarrays that can be made non-decreasing.



Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
Intuition
Solve it in one-pass with stack + sliding window.

GPT Explanation
Reverse the Array: The array is reversed to allow handling non-decreasing subarrays using a monotonic decreasing
property while iterating forward.

Deque for Monotonic Stack: The deque (q) is used to maintain indices of elements in a decreasing order as we process the
array. This helps efficiently track the ranges of subarrays and the cost of making them non-decreasing.

Sliding Window: The solution uses a sliding window approach with pointers i and j. j represents the current end of the
window, and i represents its start.

Maintaining the Monotonicity:

While adding a new element at index j to the deque, if it breaks the monotonicity (i.e., it's greater than the last
element in the deque), elements are popped from the deque. For every popped element, the contribution of its range to
the "cost" (k) is subtracted. Adjusting the Window:

If the cost exceeds k after including the current subarray, the window's start (i) is advanced until the cost is within
bounds. While doing this, elements at the start of the deque are also removed if they are no longer part of the window.
Count Valid Subarrays: The number of valid subarrays ending at j is added to the result (res) as j - i + 1.
 */
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        reverse(nums.begin(), nums.end());

        long long rst = 0;
        deque<int> decreasing_q;
        for (int end = 0, start = 0; end < n; ++end) {
            while (!decreasing_q.empty() && nums[decreasing_q.back()] < nums[end]) {
                int right_idx = decreasing_q.back();
                decreasing_q.pop_back();

                int left_idx = decreasing_q.empty() ? start - 1 : decreasing_q.back();
                // it means all the values already in the window needs to increase by nums[end] - nums[right_idx]
                // in order to add the nums[end] to the window
                k -= 1L * (right_idx - left_idx) * (nums[end] - nums[right_idx]);
            }
            decreasing_q.push_back(end);

            while (k < 0) {
                // decreasing_q.front() is the pos of the largest element in the current window
                // so all values from window_start to decreasing_q.front(),
                // will be at least the val of nums[decreasing_q.front()];
                // so when we pop nums[start] out of the window, we recover nums[decreasing_q.front()] - nums[start]
                k += nums[decreasing_q.front()] - nums[start];
                if (decreasing_q.front() == start) {
                    decreasing_q.pop_front();
                }
                start += 1;
            }
            rst += end - start + 1;
        }
        return rst;
    }
};