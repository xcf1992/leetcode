/*
75. Sort Colors

Given an array with n objects colored red, white or blue,
sort them in-place so that objects of the same color are adjacent,
with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Example:
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's,
then overwrite array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?
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
    void sortColors(vector<int>& nums) {
        int first = 0;
        int last = nums.size() - 1;
        int cur = 0;
        while (cur <= last) {
            if (nums[cur] == 0) {
                // cause the part before cur will always be 0 or 1 already, so we do not need to check cur again after
                // swap
                swap(nums[first], nums[cur]);
                first += 1;
                cur += 1;
            } else if (nums[cur] == 2) {
                // we do not know the value in last, so we cannot move cur, and need to check it again
                swap(nums[last], nums[cur]);
                last -= 1;
            } else {
                cur += 1;
            }
        }
    }
};