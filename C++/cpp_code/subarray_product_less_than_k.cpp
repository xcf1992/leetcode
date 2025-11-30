/*
713. Subarray Product Less Than K
https://leetcode.com/problems/subarray-product-less-than-k/

Your are given an array of positive integers nums.
Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than
k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2,
6]. Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Note:
0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.
*/
#include <iostream>
#include <sstream>
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
    // O(n)
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (nums.empty()) {
            return 0;
        }

        int start = 0;
        int result = 0;
        int product = 1;
        for (int end = 0; end < nums.size(); end++) {
            product *= nums[end];
            while (start <= end and product >= k) {
                product /= nums[start++];
            }
            result += end - start + 1;
        }
        return result;
    }
};

class Solution1 {
    // O(nlogn)
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }

        vector<double> preSum(n + 1, 0.0);
        for (int i = 0; i < n; ++i) {
            preSum[i + 1] = preSum[i] + log10(nums[i]);
        }

        int result = 0;
        for (int i = 0; i <= n; ++i) {
            double target = preSum[i] + log10(k);
            auto it = lower_bound(preSum.begin(), preSum.end(), target, [&](double a, double b) { return a < b; });
            int index = (it - preSum.begin()) - 1;
            if (index >= i) {
                result += index - i;
            }
        }
        return result;
    }
};