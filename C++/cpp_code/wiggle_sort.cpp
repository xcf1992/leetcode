/*
280. Wiggle Sort
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

Example:

Input: nums = [3,5,2,1,6,4]
Output: One possible answer is [3,5,1,6,2,4]
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
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if ((i & 1) and nums[i] < nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
            if (!(i & 1) and nums[i] > nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
        }
    }
};