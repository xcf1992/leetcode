/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &num) {
        if (num.size() <= 2 || (num.size() == 3 && num[0] + num[1] + num[2] != 0)) {
            return {};
        }
        
        sort(num.begin(), num.end());
        int oldVal = num[0];
        vector<vector<int>> results;
        for (int i = 0; i < num.size(); i++) {
            if (i > 0 && num[i] == oldVal) {
                continue;
            }
            oldVal = num[i];
            int needed = 0 - num[i];
            int forward = i + 1;
            int backward = num.size() - 1;
            
            while (forward < backward) {
                while (forward > i + 1 and num[forward] == num[forward - 1]) {
                    forward++;
                }
                while (backward < num.size() - 1 and num[backward] == num[backward + 1]) {
                    backward--;
                }
                if (forward >= backward) {
                    break;
                }

                if (num[forward] + num[backward] == needed) {
                    results.push_back({num[i], num[forward], num[backward]});
                    forward++;
                }
                else if (num[forward] + num[backward] < needed) {
                    forward++;
                }
                else if (num[forward] + num[backward] > needed) {
                    backward--;
                }
            }
        } 
        return results;
    }
};