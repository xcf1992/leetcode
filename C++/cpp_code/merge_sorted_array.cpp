/*
88. Merge Sorted Array
https://leetcode.com/problems/merge-sorted-array/

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from
nums2.

Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
Output: [1,2,2,3,5,6]
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int aP = m - 1;
        int bP = n - 1;
        int cur = m + n - 1;
        while (aP >= 0 and bP >= 0) {
            if (nums2[bP] > nums1[aP]) {
                nums1[cur] = nums2[bP];
                bP--;
            } else {
                nums1[cur] = nums1[aP];
                aP--;
            }
            cur--;
        }
        while (bP >= 0) {
            nums1[cur] = nums2[bP];
            bP--;
            cur--;
        }
    }
};