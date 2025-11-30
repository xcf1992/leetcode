/*
1121. Divide Array Into Increasing Sequences
Given a non-decreasing array of positive integers nums and an integer K,
find out if this array can be divided into one or more disjoint increasing subsequences of length at least K.

Example 1:

Input: nums = [1,2,2,3,3,4,4], K = 3
Output: true
Explanation:
The array can be divided into the two subsequences [1,2,3,4] and [2,3,4] with lengths at least 3 each.
Example 2:

Input: nums = [5,6,6,7,8], K = 3
Output: false
Explanation:
There is no way to divide the array using the conditions required.

Note:

1 <= nums.length <= 10^5
1 <= K <= nums.length
1 <= nums[i] <= 10^5
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
using namespace std;

class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        int n = nums.size();
        int maxCount = 1;
        int cur = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) {
                cur += 1;
            } else {
                cur = 1;
            }
            maxCount = max(cur, maxCount);
        }
        return n >= K * maxCount;
    }
};