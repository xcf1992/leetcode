/*
220. Contains Duplicate III

Given an array of integers,
find out whether there are two distinct indices i and j in the array
such that the absolute difference between nums[i] and nums[j] is at most t
and the absolute difference between i and j is at most k.

Example 1:

Input: nums = [1,2,3,1], k = 3, t = 0
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1, t = 2
Output: true
Example 3:

Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false
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

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        if (n < 2 || k == 0) {
            return false;
        }

        set<long> windows;
        int left = 0;
        for (int i = 0; i < n; i++) {
            if (i - left > k) {
                windows.erase(nums[left]);
                left++;
            }

            auto it = windows.lower_bound((long)nums[i] - (long)t);
            if (it != windows.end() and *it <= ((long)nums[i] + (long)t)) {
                return true;
            }
            windows.insert(nums[i]);
        }
        return false;
    }
};
