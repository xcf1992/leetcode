/*
239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Note:
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
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
#include <map>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) {
            return {};
        }

        deque<int> window;
        for (int i = 0; i < k; i++) {
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
        }

        vector<int> result;
        result.push_back(nums[window.front()]);
        for (int i = k; i < nums.size(); i++) {
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            if (!window.empty() && i - window.front() >= k) {
                window.pop_front();
            }
            window.push_back(i);
            result.push_back(nums[window.front()]);
        }
        return result;
    }
};
