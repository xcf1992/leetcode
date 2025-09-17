/*
442. Find All Duplicates in an Array
https://leetcode.com/problems/find-all-duplicates-in-an-array/

Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array),
some elements appear twice and others appear once.

Find all the elements that appear twice in this array.
Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[2,3]
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
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            if (nums[abs(num) - 1] > 0) {
                nums[abs(num) - 1] = -nums[abs(num) - 1];
            }
            else {
                result.push_back(abs(num));
            }
        }
        return result;
    }
};
