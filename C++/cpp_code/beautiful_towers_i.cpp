/*
https://leetcode.com/problems/beautiful-towers-i/description/
2865. Beautiful Towers I

You are given an array heights of n integers representing the number of bricks in n consecutive towers. Your task is to remove some bricks to form a mountain-shaped tower arrangement. In this arrangement, the tower heights are non-decreasing, reaching a maximum peak value with one or multiple consecutive towers and then non-increasing.

Return the maximum possible sum of heights of a mountain-shaped tower arrangement.



Example 1:

Input: heights = [5,3,4,1,1]

Output: 13

Explanation:

We remove some bricks to make heights = [5,3,3,1,1], the peak is at index 0.

Example 2:

Input: heights = [6,5,3,9,2,7]

Output: 22

Explanation:

We remove some bricks to make heights = [3,3,3,9,2,2], the peak is at index 3.

Example 3:

Input: heights = [3,2,5,5,2,3]

Output: 18

Explanation:

We remove some bricks to make heights = [2,2,5,5,2,2], the peak is at index 2 or 3.



Constraints:

1 <= n == heights.length <= 103
1 <= heights[i] <= 109
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
#include <map>
using namespace std;
/*
needless to say the brute force algorithm would be O(N^2),
considering O(n) solution,
we try to set each nums[i] as the peak point, then we can compute the left sum and right rum
for the left sum we need to find the prev_less_idx with nums[prev_less_idx] < nums[i]
then left_sum will be (i - (prev_less_idx + 1) + 1) * nums[i], this are the mtns with height max nums[i]
plus left_sum[prev_less_idx], this is the left_sum with height max nums[prev_less_idx]

we do similar thing to the right, together we will get the total sum
*/
class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights) {
        int n = heights.size();
        vector<long long> left_sum(n);
        vector<long long> right_sum(n);
        stack<int> left_max_stk;
        stack<int> right_max_stk;
        for (int i = 0; i < n; i++) {
            // do the left
            while (!left_max_stk.empty() && heights[left_max_stk.top()] >= heights[i]) {
                left_max_stk.pop();
            }
            int prev_less_idx = left_max_stk.empty() ? -1 : left_max_stk.top();
            left_sum[i] = 1LL * (i - prev_less_idx) * heights[i];
            if (prev_less_idx != -1) {
                left_sum[i] += left_sum[prev_less_idx];
            }
            left_max_stk.push(i);

            // do the right
            int j = n - 1 - i;
            while (!right_max_stk.empty() && heights[right_max_stk.top()] >= heights[j]) {
                right_max_stk.pop();
            }
            int right_less_idx = right_max_stk.empty() ? n : right_max_stk.top();
            right_sum[j] = 1LL * (right_less_idx - j) * heights[j];
            if (right_less_idx != n) {
                right_sum[j] += right_sum[right_less_idx];
            }
            right_max_stk.push(j);
        }

        long long rst = 0;
        for (int i = 0; i < n; i++) {
            rst = max(rst, left_sum[i] + right_sum[i] - heights[i]);
        }
        return rst;
    }
};