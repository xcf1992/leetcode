/*
228. Summary Ranges
https://leetcode.com/problems/summary-ranges/

Given a sorted integer array without duplicates,
return the summary of its ranges.

Example 1:
Input: [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]

Example 2:
Input: [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
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
    vector<string> summaryRanges(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) {
            return {};
        }

        vector<string> result;
        int start = 0;
        while (start < n) {
            int end = start;
            while (end + 1 < n && nums[end + 1] == nums[end] + 1) {
                end += 1;
            }

            if (end == start) {
                result.push_back(to_string(nums[start]));
            } else {
                result.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
            }
            start = end + 1;
        }
        return result;
    }
};