/*
220. Contains Duplicate III
https://leetcode.com/problems/contains-duplicate-iii/

You are given an integer array nums and two integers indexDiff and valueDiff.
Find a pair of indices (i, j) such that:
i != j,
abs(i - j) <= indexDiff.
abs(nums[i] - nums[j]) <= valueDiff, and
Return true if such pair exists or false otherwise.

Example 1:
Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
Output: true
Explanation: We can choose (i, j) = (0, 3).
We satisfy the three conditions:
i != j --> 0 != 3
abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0

Example 2:
Input: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
Output: false
Explanation: After trying all the possible pairs (i, j), we cannot satisfy the three conditions, so we return false.

Constraints:
2 <= nums.length <= 105
-109 <= nums[i] <= 109
1 <= indexDiff <= nums.length
0 <= valueDiff <= 109
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
#include <set>
using namespace std;
/*
use bucket sort could reduce the time complexity to O(n)
https://leetcode.com/problems/contains-duplicate-iii/discuss/61645/AC-O(N)-solution-in-Java-using-buckets-with-explanation
*/
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        size_t n = nums.size();
        if (n <= 1 || indexDiff == 0) {
            return false;
        }

        set<long> windows;
        int left = 0;
        for (int i = 0; i < n; i++) {
            auto it = windows.lower_bound(nums[i] - valueDiff);
            if (it != windows.end() && *it <= (nums[i] + valueDiff)) {
                return true;
            }

            if (i - left == indexDiff) {
                windows.erase(nums[left]);
                left++;
            }
            windows.insert(nums[i]);
        }
        return false;
    }
};