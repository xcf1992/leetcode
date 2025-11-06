/*
15. 3Sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
Find all unique triplets in the array which gives the sum of zero.

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
    vector<vector<int>> threeSum(vector<int>& num) {
        int n = num.size();
        if (n <= 2 or (n == 3 and num[0] + num[1] + num[2] != 0)) {
            return {};
        }
        sort(num.begin(), num.end());

        vector<vector<int>> results;
        for (int i = 0; i < n; ++i) {
            if (i != 0 and num[i] == num[i - 1]) {
                continue;
            }

            int target = 0 - num[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                int sum = num[left] + num[right];
                if (sum < target) {
                    left += 1;
                } else if (sum > target) {
                    right -= 1;
                } else {
                    results.push_back({num[i], num[left], num[right]});
                    int front = num[left];
                    int back = num[right];
                    while (left < right and num[left] == front) {
                        left += 1;
                    }
                    while (left < right and num[right] == back) {
                        right -= 1;
                    }
                }
            }
        }
        return results;
    }
};
