/*
349. Intersection of Two Arrays
https://leetcode.com/problems/intersection-of-two-arrays/

Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]

Note:
Each element in the result must be unique.
The result can be in any order.
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
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        vector<int> result;
        unordered_set<int> intersection1;
        unordered_set<int> intersection2;

        for (int i = 0; i < nums1.size(); i++) {
            intersection1.insert(nums1[i]);
        }

        for (int i = 0; i < nums2.size(); i++) {
            intersection2.insert(nums2[i]);
        }

        for (auto it = intersection1.begin(); it != intersection1.end(); it++) {
            if (intersection2.find(*it) != intersection2.end()) {
                result.push_back(*it);
            }
        }
        return result;
    }
};