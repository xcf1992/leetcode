/*
https://leetcode.com/problems/maximum-erasure-value/
1695. Maximum Erasure Value

You are given an array of positive integers nums
and want to erase a subarray containing unique elements.
The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.
An array b is called to be a subarray of a if it forms a contiguous subsequence of a,
that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

Example 1:
Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
Example 2:
Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].

Constraints:
1 <= nums.length <= 105
1 <= nums[i] <= 104
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pre_sum[i + 1] = pre_sum[i] + nums[i];
        }

        int result = 0;
        unordered_map<int, int> last_pos;
        int left = -1;
        for (int i = 0; i < n; ++i) {
            if (last_pos.find(nums[i]) != last_pos.end()) {
                left = max(left, last_pos[nums[i]]);
            }
            result = max(result, pre_sum[i + 1] - pre_sum[left + 1]);
            last_pos[nums[i]] = i;
        }
        return result;
    }
};