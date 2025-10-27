/*
https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/description

2163. Minimum Difference in Sums After Removal of Elements

You are given a 0-indexed integer array nums consisting of 3 * n elements.

You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:

The first n elements belonging to the first part and their sum is sumfirst.
The next n elements belonging to the second part and their sum is sumsecond.
The difference in sums of the two parts is denoted as sumfirst - sumsecond.

For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
Return the minimum difference possible between the sums of the two parts after the removal of n elements.



Example 1:

Input: nums = [3,1,2]
Output: -1
Explanation: Here, nums has 3 elements, so n = 1.
Thus we have to remove 1 element from nums and divide the array into two equal parts.
- If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
- If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
- If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
The minimum difference between sums of the two parts is min(-1,1,2) = -1.
Example 2:

Input: nums = [7,9,5,8,1,3]
Output: 1
Explanation: Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3]. The difference in sums will be (7+9) - (1+3) = 12.
To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1. The resultant array becomes [7,5,8,3]. The difference in sums of the two parts is (7+5) - (8+3) = 1.
It can be shown that it is not possible to obtain a difference smaller than 1.


Constraints:

nums.length == 3 * n
1 <= n <= 105
1 <= nums[i] <= 105
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
using namespace std;
/*
We need to split the array into three equal parts such that the difference between the sum of the left k smallest elements and the right k largest elements is minimized.
We need a max-heap to track the k smallest elements from the left.
We need a min-heap to track the k largest elements from the right.
 */
class Solution {
public:
    long long minimumDifference(vector<int> &nums) {
        int n = nums.size();
        int k = n / 3;

        vector<long long> left_min(n);
        priority_queue<int, vector<int>, less<int> > max_heap;
        long long left_sum = 0;
        for (int i = 0; i < k; i++) {
            max_heap.push(nums[i]);
            left_sum += nums[i];
        }
        left_min[k - 1] = left_sum;
        for (int i = k; i < 2 * k; i++) {
            if (!max_heap.empty() && nums[i] < max_heap.top()) {
                left_sum += nums[i] - max_heap.top();
                max_heap.pop();
                max_heap.push(nums[i]);
            }
            left_min[i] = left_sum;
        }

        vector<long long> right_max(n);
        priority_queue<int, vector<int>, greater<int> > min_heap;
        long long right_sum = 0;
        for (int i = n - 1; i >= 2 * k; i--) {
            min_heap.push(nums[i]);
            right_sum += nums[i];
        }
        right_max[2 * k] = right_sum;
        for (int i = 2 * k - 1; i >= k - 1; i--) {
            if (!min_heap.empty() && nums[i] > min_heap.top()) {
                right_sum += nums[i] - min_heap.top();
                min_heap.pop();
                min_heap.push(nums[i]);
            }
            right_max[i] = right_sum;
        }

        long long min_diff = LLONG_MAX;
        for (int i = k - 1; i < 2 * k; i++) {
            min_diff = min(min_diff, left_min[i] - right_max[i + 1]);
        }
        return min_diff;
    }
};
