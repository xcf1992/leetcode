/*
697. Degree of an Array
Given a non-empty array of non-negative integers nums,
the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums,
that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation:
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.

Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.

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
using namespace std;

class Solution {
public:
    int findShortestSubArray(vector<int> &nums) {
        int n = nums.size();
        unordered_map<int, vector<int> > range;
        unordered_map<int, int> frequency;
        int degree = 0;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            frequency[num] += 1;
            if (range[num].size() < 2) {
                range[num].push_back(i);
            } else {
                range[num][1] = i;
            }
            degree = max(degree, frequency[num]);
        }

        if (degree == 1) {
            return 1;
        }

        int result = n;
        for (auto &it: frequency)
            if (degree == it.second) {
                int num = it.first;
                result = min(result, range[num][1] - range[num][0] + 1);
            }
        return result;
    }
};