/*
540. Single Element in a Sorted Array
https://leetcode.com/problems/single-element-in-a-sorted-array/

Given a sorted array consisting of only integers where every element appears exactly twice
except for one element which appears exactly once.
Find this single element that appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10

Note:
Your solution should run in O(log n) time and O(1) space.
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
    int singleNonDuplicate(vector<int> &nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < end) {
            int mid = start + (end - start) / 2;
            int num = nums[mid];

            if (mid < end and num
            ==
            nums[mid + 1]
            )
            {
                if ((end - mid + 1) % 2 == 0) {
                    end = mid - 1;
                } else {
                    start = mid;
                }
            }
            else
            if (mid > start and num
            ==
            nums[mid - 1]
            )
            {
                if ((end - mid) % 2 == 0) {
                    end = mid;
                } else {
                    start = mid + 1;
                }
            }
            else
            {
                return num;
            }
        }
        return nums[start];
    }
};