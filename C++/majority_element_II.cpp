/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
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
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result;
        int candidate1 = INT_MIN;
        int count1 = 0;
        int candidate2 = INT_MIN;
        int count2 = 0;
        for (int num : nums) {
            if (candidate1 == num) {
                count1 += 1;
            }
            else if (candidate2 == num) {
                count2 += 1;
            }
            else if (count1 == 0) {
                candidate1 = num;
                count1 += 1;
            }
            else if (count2 == 0) {
                candidate2 = num;
                count2 += 1;
            }
            else {
                count1 -= 1;
                count2 -= 1;
            }
        }
        
        count1 = count2 = 0;
        for (int num : nums) {
            if (num == candidate1) {
                count1 += 1;
            }
            else if (num == candidate2) {
                count2 += 1;
            }
        }
        
        if (count1 > nums.size() / 3) {
            result.push_back(candidate1);
        }
        if (count2 > nums.size() / 3) {
            result.push_back(candidate2);
        }
        return result;
    }
};
