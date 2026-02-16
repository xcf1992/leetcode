/*
1712. Ways to Split Array Into Three Subarrays
https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/

A split of an integer array is good if:
The array is split into three non-empty contiguous subarrays -
named left, mid, right respectively from left to right.
The sum of the elements in left is less than or equal to the sum of the elements in mid,
and the sum of the elements in mid is less than or equal to the sum of the elements in right.
Given nums, an array of non-negative integers, return the number of good ways to split nums.
As the number may be too large, return it modulo 109 + 7.

Example 1:
Input: nums = [1,1,1]
Output: 1
Explanation: The only good way to split nums is [1] [1] [1].
Example 2:
Input: nums = [1,2,2,2,5,0]
Output: 3
Explanation: There are three good ways of splitting nums:
[1] [2] [2,2,5,0]
[1] [2,2] [2,5,0]
[1,2] [2,2] [5,0]
Example 3:
Input: nums = [3,2,1]
Output: 0
Explanation: There is no good way to split nums.

Constraints:
3 <= nums.length <= 105
0 <= nums[i] <= 104
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
/*
https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/discuss/999257/C%2B%2BJavaPython-O(n)-with-picture

The approach is not too hard,
but the implementation was tricky for me to get right.

First, we prepare the prefix sum array,
so that we can compute subarray sums in O(1).
Then, we move the boundary of the first subarray left to right.
This is the first pointer - i.

For each point i, we find the minimum (j) and maximum (k) boundaries of the second subarray:
nums[j] >= 2 * nums[i]
nums[sz - 1] - nums[k] >= nums[k] - nums[i]
Note that in the code and examples below,
k points to the element after the second array.
In other words, it marks the start of the (shortest) third subarray.
 This makes the logic a bit simpler.

With these conditions,
sum(0, i) <= sum(i + 1, j),
and sum(i + 1, k - 1) < sum(k, n).
Therefore, for a point i, we can build k - j subarrays satisfying the problem requirements.
Final thing is to realize that j and k will only move forward,
which result in a linear-time solution.

The following picture demonstrate this approach for the [4,2,3,0,3,5,3,12] test case.
*/
class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        int rst = 0;
        int n = nums.size();
        int mod = 1e9 + 7;
        partial_sum(begin(nums), end(nums), begin(nums));
        for (int i = 0, j = 0, k = 0; i < n - 2; ++i) {
            while (j <= i || (j < n - 1 && nums[j] < nums[i] * 2)) {
                j += 1;
            }

            while (k < j || (k < n - 1 && nums[k] - nums[i] <= nums[n - 1] - nums[k])) {
                k += 1;
            }
            rst = (rst + k - j) % mod;
        }
        return rst;
    }
};