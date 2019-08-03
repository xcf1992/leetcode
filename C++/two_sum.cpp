/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
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
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result;
        unordered_map<int, int> indexes;
        for (int i = 0; i < numbers.size(); i++) {
            int needed = target - numbers[i];
            if (indexes.find(needed) != indexes.end()) {
                result.push_back(indexes[needed]);
                result.push_back(i);
                break;
            }
            indexes[numbers[i]] = i;
        }
        return result;
    }
};
