/*
https://leetcode.com/problems/steps-to-make-array-non-decreasing/description/
2289. Steps to Make Array Non-decreasing

You are given a 0-indexed integer array nums. In one step, remove all elements nums[i] where nums[i - 1] > nums[i] for
all 0 < i < nums.length.

Return the number of steps performed until nums becomes a non-decreasing array.



Example 1:

Input: nums = [5,3,4,4,7,3,6,11,8,5,11]
Output: 3
Explanation: The following are the steps performed:
- Step 1: [5,3,4,4,7,3,6,11,8,5,11] becomes [5,4,4,7,6,11,11]
- Step 2: [5,4,4,7,6,11,11] becomes [5,4,7,11,11]
- Step 3: [5,4,7,11,11] becomes [5,7,11,11]
[5,7,11,11] is a non-decreasing array. Therefore, we return 3.
Example 2:

Input: nums = [4,5,7,7,13]
Output: 0
Explanation: nums is already a non-decreasing array. Therefore, we return 0.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
Problem Recap 📌
You are given an array nums.

Every step, remove all elements nums[i] such that:

nums[i] < nums[i - 1]
These removals are simultaneous.

Return the number of steps until the array becomes stable (no more removals).

Intuition / Approach 💡
Observation 👀
A number gets removed only when there is a greater element on its left that outlives it.

This creates a chain of dependencies, where each element has a specific number of steps before it gets eliminated.

Why stack? ⚡
We use a monotonic decreasing stack storing:

(value, stepsBeforeRemoval)
When encountering a new number:

Pop all elements ≤ current
→ Those elements cannot kill the current one
→ Current inherits their maximum step count
If a greater element remains
→ Current element dies exactly 1 step after that
Track global maximum
This gives the exact steps for each element in O(n) time.

-=-=-=-=

Let's start with an example, I use blocks of different height to represent the values:

The 1st number is always here since there is no larger number on its left.
The 2nd number will be removed 'by' the first number in the first step.
The 3rd number will be removed 'by' the second number in the first step.
The 4th number will be removed 'by' the 2nd number, after the first step when the 3rd block is removed. Thus the step
for the 4th number is step_for_the_3rd_number + 1 = 2. image

Therefore, for a number A[i], assume the first larger number on its left is A[lft]. A[i] can only be removed after all
the numbers within (lft, i) are removed, and its step equals the largest step within (lft, i) plus 1.

Thus we can maintain a monotonic decreasing stack, and traverse the array from left to right. For each newly added
number A[i], (recall the example at the begining) we need to:

remove the top number from stack that is no larger than A[i], and record the maximum step number from these popped
numbers.

Until we find the first number that is larger than A[i], meaning A[i] will be removed 'by' this number in some step, and
this step number equals the maximum step number we removed plus 1.

In the picture below, for the number in cyan, we popped the number to be removed in step 2 and step 3, thus the cyan
number will be removed in step 3 + 1.
 */
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        stack<pair<int, int>> min_stk;
        int rst = 0;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            while (!min_stk.empty() && nums[min_stk.top().first] <= nums[i]) {
                cnt = max(min_stk.top().second, cnt);
                min_stk.pop();
            }

            if (!min_stk.empty()) {
                cnt += 1;
            }
            rst = max(rst, cnt);
            min_stk.push({i, cnt});
        }
        return rst;
    }
};