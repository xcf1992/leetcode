/*
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/

Given an array of integers arr and an integer target.

You have to find two non-overlapping sub-arrays of arr each with sum equal target.
There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays,
or return -1 if you cannot find such two sub-arrays.

Example 1:
Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.

Example 2:
Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.

Example 3:
Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.

Example 4:
Input: arr = [5,5,4,4,5], target = 3
Output: -1
Explanation: We cannot find a sub-array of sum = 3.

Example 5:
Input: arr = [3,1,1,1,5,1,2,1], target = 3
Output: 3
Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 1000
1 <= target <= 10^8
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
#include <map>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        unordered_map<int, int> hmap;
        int sum = 0;
        int lsize = INT_MAX;
        int result = INT_MAX;
        hmap[0] = -1;
        for (int i = 0; i < arr.size(); i++){
            sum += arr[i];
            hmap[sum] = i; // stores key as sum upto index i, and value as i.
        }

        sum = 0;
        for (int i = 0; i < arr.size(); i++){
            sum += arr[i];
            if (hmap.find(sum - target) != hmap.end()) {
                lsize = min(lsize, i - hmap[sum-target]);
                // stores minimum length of sub-array starting with index<= i with sum target. This ensures non- overlapping property.
            }

            //hmap.get(sum+target) searches for any sub-array starting with index i+1 with sum target.
            if (hmap.find(sum + target) != hmap.end() and lsize < INT_MAX) {
                result = min(result, hmap[sum + target] - i + lsize); // updates the result only if both left and right sub-array exists.
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};
