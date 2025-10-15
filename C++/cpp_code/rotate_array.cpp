/*
189. Rotate Array
https://leetcode.com/problems/rotate-array/description/?envType=company&envId=netflix&favoriteSlug=netflix-all

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:
1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105

Follow up:
Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    void reverse(vector<int>& nums, int begin, int end) {
        while (begin < end) {
            swap(nums[begin], nums[end]);
            begin += 1;
            end -= 1;
        }
    }
public:
    void rotate(vector<int>& nums, int k) {
        size_t cnt = nums.size();
        k = k % cnt;
        if (cnt <= 1 || k == 0) {
            return;
        }

        reverse(nums, 0, cnt - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, cnt - 1);
    }
};
