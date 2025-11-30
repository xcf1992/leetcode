/*
https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/description/
3397. Maximum Number of Distinct Elements After Operations

You are given an integer array nums and an integer k.

You are allowed to perform the following operation on each element of the array at most once:

Add an integer in the range [-k, k] to the element.
Return the maximum possible number of distinct elements in nums after performing the operations.



Example 1:

Input: nums = [1,2,2,3,3,4], k = 2

Output: 6

Explanation:

nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.

Example 2:

Input: nums = [4,4,4,4], k = 1

Output: 3

Explanation:

By adding -1 to nums[0] and 1 to nums[1], nums changes to [3, 5, 4, 4].



Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
0 <= k <= 109
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
#include <numeric>
using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int rst = 1;
        int prev = nums[0] - k;
        for (int i = 1; i < nums.size(); i++) {
            int cur = max(nums[i] - k, prev + 1);
            if (cur <= nums[i] + k) {
                prev = cur;
                rst += 1;
            }
        }
        return rst;
    }
};
