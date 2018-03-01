//
//  sliding_window_maximum.cpp
//  C++
//
//  Created by Chenfu Xie on 2/28/18.
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

/*
 Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 
 For example,
 Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
 
 Window position                Max
 ---------------               -----
 [1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
 Therefore, return the max sliding window as [3,3,5,5,6,7].
 
 Note:
 You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
 */

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (nums.empty()) {
            return result;
        }
        deque<int> window;
        
        for (int i = 0; i < k; i++) {
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
        }
        
        for (int i = k; i < nums.size(); i++) {
            result.push_back(nums[window.front()]);
            
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            if (!window.empty() && i - window.front() >= k) {
                window.pop_front();
            }
            window.push_back(i);
        }
        result.push_back(nums[window.front()]);
        return result;
    }
};
