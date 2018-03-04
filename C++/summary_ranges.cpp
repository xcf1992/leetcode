/*
 Given a sorted integer array without duplicates, return the summary of its ranges.
 
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
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ranges;
        int n = nums.size();
        if (n == 0) {
            return ranges;
        }
        for (int i = 0; i < n;) {
            int start = i;
            int end = i;
            while (end + 1 < n && nums[end + 1] == nums[end] + 1) {
                end += 1;
            }
            ranges.push_back(to_string(nums[start]));
            if (end > start) {
                ranges.back() + "->" + to_string(nums[end]);
            }
            i = end + 1;
        }
        return ranges;
    }
};
