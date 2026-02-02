/*
https://leetcode.com/problems/longest-balanced-subarray-i/description/
3719. Longest Balanced Subarray I

You are given an integer array nums.

A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct
odd numbers.

Return the length of the longest balanced subarray.



Example 1:

Input: nums = [2,5,4,3]

Output: 4

Explanation:

The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.
Example 2:

Input: nums = [3,2,2,5,4]

Output: 5

Explanation:

The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.
Example 3:

Input: nums = [1,2,3,2]

Output: 3

Explanation:

The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.


Constraints:

1 <= nums.length <= 1500
1 <= nums[i] <= 105
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
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int max_len = INT_MIN;
        for (int i = 0; i < n; i++) {
            unordered_set<int> odd_freq;
            unordered_set<int> even_freq;
            for (int j = i; j < n; j++) {
                if (nums[j] % 2 == 0) {
                    even_freq.insert(nums[j]);
                } else {
                    odd_freq.insert(nums[j]);
                }
                if (even_freq.size() == odd_freq.size()) {
                    max_len = max(max_len, j - i + 1);
                }
            }
        }
        return max_len == INT_MIN ? 0 : max_len;
    }
};