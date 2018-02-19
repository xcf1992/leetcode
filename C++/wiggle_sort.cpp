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

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].


*/
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (i & 1 && nums[i] < nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
            else if (!(i & 1) && nums[i] > nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
        }
        return;
    }
};
