//
//  find_pivot_index.cpp
//  C++
//
//  Created by Chenfu Xie on 1/20/18.
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
public:
    int pivotIndex(vector<int>& nums) {
        if (nums.size() < 3) {
            return -1;
        }
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        int left = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (left << 1 == sum - nums[i]) {
                return i;
            }
            left += nums[i];
        }
        return -1;
    }
};
