/*
350. Intersection of Two Arrays II
https://leetcode.com/problems/intersection-of-two-arrays-ii/

Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.

Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk,
and the memory is limited such that you cannot load all elements into the memory at once?
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
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        unordered_map<int, int> intersection;
        for (int i = 0; i < nums1.size(); i++) {
            intersection[nums1[i]] += 1;
        }

        for (int i = 0; i < nums2.size(); i++) {
            if (intersection.find(nums2[i]) != intersection.end() and intersection[nums2[i]] > 0) {
                result.push_back(nums2[i]);
                intersection[nums2[i]] -= 1;
            }
        }
        return result;
    }
};