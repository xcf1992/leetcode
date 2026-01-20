/*
https://leetcode.com/problems/continuous-subarrays/description/
2762. Continuous Subarrays

You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:

Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] -
nums[i2]| <= 2. Return the total number of continuous subarrays.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [5,4,2,4]
Output: 8
Explanation:
Continuous subarray of size 1: [5], [4], [2], [4].
Continuous subarray of size 2: [5,4], [4,2], [2,4].
Continuous subarray of size 3: [4,2,4].
There are no subarrys of size 4.
Total continuous subarrays = 4 + 3 + 1 = 8.
It can be shown that there are no more continuous subarrays.


Example 2:

Input: nums = [1,2,3]
Output: 6
Explanation:
Continuous subarray of size 1: [1], [2], [3].
Continuous subarray of size 2: [1,2], [2,3].
Continuous subarray of size 3: [1,2,3].
Total continuous subarrays = 3 + 2 + 1 = 6.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int min_cap = 0;
        int max_cap = 0;
        int left_idx = 0;
        long long rst = 0;
        for (int right_idx = 0; right_idx < nums.size(); right_idx++) {
            if (right_idx == 0) {  // First element
                rst += 1;
                min_cap = nums[right_idx] - 2;  // range from a - 2
                max_cap = nums[right_idx] + 2;  // range to a + 2
            } else if (nums[right_idx] >= min_cap && nums[right_idx] <= max_cap) {
                // If new element belong to same range then
                min_cap = max(min_cap, nums[right_idx] - 2);  // take max from (a-2,b-2)
                max_cap = min(max_cap, nums[right_idx] + 2);  // take min from (a+2,b+2)
                rst += right_idx - left_idx + 1;
            } else {
                // If doest not belong to ranges try to remove from i-1
                left_idx = right_idx - 1;
                min_cap = nums[right_idx] - 2;
                max_cap = nums[right_idx] + 2;
                while (nums[left_idx] >= nums[right_idx] - 2 && nums[left_idx] <= nums[right_idx] + 2) {
                    min_cap = max(min_cap, nums[left_idx] - 2);  // take max
                    max_cap = min(max_cap, nums[left_idx] + 2);  // take min
                    left_idx--;
                }
                left_idx++;

                rst = rst + (right_idx - left_idx + 1);
            }
        }
        return rst;
    }
};

class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        long long rst = 0;
        int n = nums.size();
        multiset<int> window;
        long long right = 0;
        long long left = 0;
        while (right < n) {
            window.insert(nums[right]);

            while (!window.empty() && *window.rbegin() - *window.begin() > 2) {
                window.erase(window.find(nums[left]));
                left += 1;
            }

            rst += right - left + 1;
            right += 1;
        }
        return rst;
    }
};