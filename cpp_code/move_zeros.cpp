/*
283. Move Zeroes
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int zeroP = 0;
        int notZeroP = 0;
        for (; notZeroP < n; ++notZeroP) if (nums[notZeroP] != 0) {
            nums[zeroP] = nums[notZeroP];
            zeroP++;
        }
        for (; zeroP < n; ++zeroP) {
            nums[zeroP] = 0;
        }
    }
};

/*
wrong, the order should not be changed

Input
[0,1,0,3,12]
Output
[12,1,3,0,0]
Expected
[1,3,12,0,0]
*/
class Solution1 {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return;
        }

        int left = 0;
        int right = n - 1;
        while (left < right) {
            if (nums[left] != 0) {
                left += 1;
                continue;
            }
            if (nums[right] == 0) {
                right -= 1;
                continue;
            }
            swap(nums[left], nums[right]);
            left += 1;
            right -= 1;
        }
    }
};
