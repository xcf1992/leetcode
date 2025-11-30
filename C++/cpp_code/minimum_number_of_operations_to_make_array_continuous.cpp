/*
https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/description/
2009. Minimum Number of Operations to Make Array Continuous

You are given an integer array nums. In one operation, you can replace any element in nums with any integer.

nums is considered continuous if both of the following conditions are fulfilled:

All elements in nums are unique.
The difference between the maximum element and the minimum element in nums equals nums.length - 1.
For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.

Return the minimum number of operations to make nums continuous.



Example 1:

Input: nums = [4,2,5,3]
Output: 0
Explanation: nums is already continuous.
Example 2:

Input: nums = [1,2,3,5,6]
Output: 1
Explanation: One possible solution is to change the last element to 4.
The resulting array is [1,2,3,5,4], which is continuous.
Example 3:

Input: nums = [1,10,100,1000]
Output: 3
Explanation: One possible solution is to:
- Change the second element to 2.
- Change the third element to 3.
- Change the fourth element to 4.
The resulting array is [1,2,3,4], which is continuous.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
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
using namespace std;

/*
we need to minimize the final result,
so when we consider each nums[i] as the start point, and try to find the minimum operations we need
in order to make the whole nums array continuous;
that is why we use rst = min(rst, n - (j - i));
 */
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        // std::set automatically sorts
        set<int> unique(nums.begin(), nums.end());
        vector<int> new_nums;
        for (int num : unique) {
            new_nums.push_back(num);
        }

        int j = 0;
        int rst = n;
        for (int i = 0; i < new_nums.size(); i++) {
            while (j < new_nums.size() && new_nums[j] < new_nums[i] + n) {
                j += 1;
            }
            rst = min(rst, n - (j - i));
        }

        return rst;
    }
};