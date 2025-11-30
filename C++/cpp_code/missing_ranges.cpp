/*
163. Missing Ranges
https://leetcode.com/problems/missing-ranges/

Given a sorted integer array nums,
where the range of elements are in the inclusive range [lower, upper],
return its missing ranges.

Example:
Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
Output: ["2", "4->49", "51->74", "76->99"]
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
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        if (nums.empty()) {
            if (lower == upper) {
                return {to_string(lower)};
            }
            return {to_string(lower) + "->" + to_string(upper)};
        }

        vector<string> result;
        long left = lower;
        long right = upper;
        for (int i = 0; i < nums.size(); ++i) {
            long cur = nums[i];
            if (left + 1 == cur) {
                result.push_back(to_string(left));
            } else if (left + 1 < cur) {
                result.push_back(to_string(left) + "->" + to_string(cur - 1));
            }
            left = cur + 1;
        }

        if (left == right) {
            result.push_back(to_string(left));
        } else if (left < right) {
            result.push_back(to_string(left) + "->" + to_string(right));
        }
        return result;
    }
};