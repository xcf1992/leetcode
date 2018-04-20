/*
 Note: This is an extension of House Robber.
 
 After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
 
 Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return nums.front();
        }
        if (n == 2) {
            return max(nums[0], nums[1]);
        }
        
        int twoBefore = nums[0];
        int oneBefore = nums[0];
        int result = max(oneBefore, twoBefore);
        for (int i = 2; i < n - 1; i++) {
            int cur = max(twoBefore + nums[i], oneBefore);
            result = max(result, cur);
            twoBefore = oneBefore;
            oneBefore = cur;
        }
        
        oneBefore = nums[1];
        twoBefore = 0;
        for (int i = 2; i < n; i++) {
            int cur = max(twoBefore + nums[i], oneBefore);
            result = max(result, cur);
            twoBefore = oneBefore;
            oneBefore = cur;
        }
        return result;
    }
};
