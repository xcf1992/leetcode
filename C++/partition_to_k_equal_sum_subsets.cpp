//
//  partition_to_k_equal_sum_subsets.cpp
//  C++
//
//  Created by Chenfu Xie on 1/31/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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
#include <map>
using namespace std;

class Solution {
private:
    bool partition(vector<int>& nums, vector<int>& taken, int start, int k, int curSum, int target) {
        if (k == 0) {
            return true;
        }
        
        if (curSum == target) {
            return partition(nums, taken, 0, k - 1, 0, target);
        }
        for (int i = start; i < nums.size(); i++) {
            if (!taken[i] && curSum + nums[i] <= target) {
                taken[i] = true;
                if (partition(nums, taken, i + 1, k, curSum + nums[i], target)) {
                    return true;
                }
                taken[i] = false;
            }
        }
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum % k != 0) {
            return false;
        }
        vector<int> taken(nums.size(), false);
        return partition(nums, taken, 0, k, 0, sum / k);
    }
};
