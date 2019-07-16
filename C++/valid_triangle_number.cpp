/*
611. Valid Triangle Number
Given an array consists of non-negative integers,
your task is to count the number of triplets chosen from the array that can make triangles
if we take them as side lengths of a triangle.

Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are:
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].
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
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }
        sort(nums.begin(), nums.end());

        int result = 0;
        for (int i = n - 1; i > 1; i--) {
            int j = i - 1;
            int k = 0;
            while (k < j) {
                if (nums[k] + nums[j] > nums[i]) {
                    result += j - k;
                    j -= 1;
                }
                else {
                    k += 1;
                }
            }
        }
        return result;
    }
};
