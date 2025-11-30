/*
https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/description/
2099. Find Subsequence of Length K With the Largest Sum

You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the
largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the
order of the remaining elements.



Example 1:

Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation:
The subsequence has the largest sum of 3 + 3 = 6.
Example 2:

Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation:
The subsequence has the largest sum of -1 + 3 + 4 = 6.
Example 3:

Input: nums = [3,4,3,3], k = 2
Output: [3,4]
Explanation:
The subsequence has the largest sum of 3 + 4 = 7.
Another possible subsequence is [4, 3].


Constraints:

1 <= nums.length <= 1000
-105 <= nums[i] <= 105
1 <= k <= nums.length
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int, int>> num_pos;
        for (int i = 0; i < nums.size(); i++) {
            num_pos.push_back({nums[i], i});
        }
        sort(num_pos.begin(), num_pos.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first;
        });

        vector<pair<int, int>> top_k_nums(num_pos.begin(), num_pos.begin() + k);
        sort(top_k_nums.begin(), top_k_nums.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.second < b.second;
        });

        vector<int> rst;
        for (auto& [num, _] : top_k_nums ) {
            rst.push_back(num);
        }
        return rst;
    }
};
