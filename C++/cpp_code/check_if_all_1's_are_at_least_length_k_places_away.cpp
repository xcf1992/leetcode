/*
1437. Check If All 1's Are at Least Length K Places Away
https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/

Given an array nums of 0s and 1s and an integer k,
return True if all 1's are at least k places away from each other,
otherwise return False.

Example 1:
Input: nums = [1,0,0,0,1,0,0,1], k = 2
Output: true
Explanation: Each of the 1s are at least 2 places away from each other.

Example 2:
Input: nums = [1,0,0,1,0,1], k = 2
Output: false
Explanation: The second 1 and third 1 are only one apart from each other.

Example 3:
Input: nums = [1,1,1,1,1], k = 0
Output: true

Example 4:
Input: nums = [0,1,0,1], k = 1
Output: true

Constraints:
1 <= nums.length <= 10^5
0 <= k <= nums.length
nums[i] is 0 or 1
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
#include <set>
#include <numeric>

using namespace std;

class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int last = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                continue;
            }

            if (last == -1) {
                last = i;
                continue;
            }

            if (i - last - 1 >= k) {
                last = i;
                continue;
            }
            return false;
        }
        return true;
    }
};
