/*
689. Maximum Sum of 3 Non-Overlapping Subarrays
In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed).
If there are multiple answers, return the lexicographically smallest one.

Example:

Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.


Note:

nums.length will be between 1 and 20000.
nums[i] will be between 1 and 65535.
k will be between 1 and floor(nums.length / 3).
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

/*
The question asks for three non-overlapping intervals with maximum sum of all 3 intervals.
If the middle interval is [i, i+k-1], where k <= i <= n-2k,
the left interval has to be in subrange [0, i-1],
and the right interval is from subrange [i+k, n-1].

So the following solution is based on DP.

posLeft[i] is the starting index for the left interval in range [0, i];
posRight[i] is the starting index for the right interval in range [i, n-1];
*/
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum = {0};
        for (int i : nums) {
            sum.push_back(sum.back() + i);
        }

        vector<int> posLeft(n, 0);
        int curMax = sum[k] - sum[0];
        for (int i = k; i < n; i++) {
            posLeft[i] = posLeft[i - 1];
            if (sum[i + 1] - sum[i + 1 - k] > curMax) {
                posLeft[i] = i - k + 1;
                curMax = sum[i + 1] - sum[i + 1 - k];
            }
        }

        vector<int> posRight(n, n - k);
        curMax = sum[n] - sum[n - k];
        for (int i = n - k - 1; i >= 0; i--) {
            posRight[i] = posRight[i + 1];
            if (sum[i + k] - sum[i] >= curMax) { // as we prefer lexicographically smaller result, so even sum is equal we will update when check backwardly
                posRight[i] = i;
                curMax = sum[i + k] - sum[i];
            }
        }

        int maxSum = 0;
        vector<int> result(3, 0);
        for (int i = k; i <= n - 2 * k; i++) {
            int left = posLeft[i - 1];
            int right = posRight[i + k];
            curMax = sum[left + k] - sum[left] +
                   sum[i + k] - sum[i] +
                   sum[right + k] - sum[right];
            if (curMax > maxSum) {
                maxSum = curMax;
                result = {left, i, right};
            }
        }
        return result;
    }
};
