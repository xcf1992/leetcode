/*
 Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.
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
        if (nums.size() < 2 || k == 0) {
            return false;
        }
        set<long> windows;
        int left = 0;
        for (int i = 0; i < nums.size(); i++){
            if (i - left > k){
                windows.erase(nums[left]);
                left++;
            }
            set<long>::iterator it = windows.lower_bound((long)nums[i] - (long)t);
            if (it != windows.end() && *it <= ((long)nums[i] + (long)t)) {
                return true;
            }
            windows.insert(nums[i]);
        }
        return false;
    }
};
