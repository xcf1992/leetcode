/*
https://leetcode.com/problems/maximum-subarray-sum-after-one-operation/description/
1746. Maximum Subarray Sum After One Operation

You are given an integer array nums. You must perform exactly one operation where you can replace one element nums[i]
with nums[i] * nums[i].

Return the maximum possible subarray sum after exactly one operation. The subarray must be non-empty.



Example 1:

Input: nums = [2,-1,-4,-3]
Output: 17
Explanation: You can perform the operation on index 2 (0-indexed) to make nums = [2,-1,16,-3]. Now, the maximum subarray
sum is 2 + -1 + 16 = 17. Example 2:

Input: nums = [1,-1,1,1,-1,-1,1]
Output: 4
Explanation: You can perform the operation on index 1 (0-indexed) to make nums = [1,1,1,1,-1,-1,1]. Now, the maximum
subarray sum is 1 + 1 + 1 + 1 = 4.


Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
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
using namespace std;

/*
Let’s define a 2D table dp[n][2], where:

dp[index][0] represents the maximum sum of a subarray ending at index with no squared elements.
dp[index][1] represents the maximum sum of a subarray ending at index with exactly one squared element.
 */
class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        // Maximum sum with no squared element is just the
        dp[0][0] = nums[0];
        // Maximum sum with the first element squared.
        dp[0][1] = nums[0] * nums[0];
        int rst = nums[0] * nums[0];
        for (int index = 1; index < n; index++) {
            // Option 1: Start a new subarray.
            // Option 2: Continue the previous subarray.
            dp[index][0] = max(nums[index], dp[index - 1][0] + nums[index]);

            // Option 1: Start a new subarray.
            // Option 2: Square the current element
            // Option 3: Do not square the element.
            dp[index][1] = max(max(nums[index] * nums[index], dp[index - 1][0] + nums[index] * nums[index]),
                               dp[index - 1][1] + nums[index]);

            // Update maxSum
            rst = max(rst, dp[index][1]);
        }

        return rst;
    }
};