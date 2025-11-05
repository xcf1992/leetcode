/*
561. Array Partition I
Given an array of 2n integers,
your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn)
which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
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
    // bucket sort
public:
    int arrayPairSum(vector<int> &nums) {
        int limit = 10000;
        vector<int> arr(20001, 0);
        for (int num: nums) {
            arr[num + limit] += 1;
        }

        int result = 0;
        int d = 0; // d means how many elements has been used in current bucket
        for (int i = -10000; i <= 10000; ++i) {
            result += (arr[i + limit] + 1 - d) / 2 * i;
            d = (2 + arr[i + limit] - d) % 2;
        }
        return result;
    }
};

class Solution1 {
public:
    int arrayPairSum(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
        }
        return sum;
    }
};