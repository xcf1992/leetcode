/*
548. Split Array with Equal Sum
Given an array with n integers,
you need to find if there are triplets (i, j, k) which satisfies following conditions:

0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array
starting from the element indexed L to the element indexed R.

Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5.
preSum(0, i - 1) = preSum(0, 0) = 1
preSum(i + 1, j - 1) = preSum(2, 2) = 1
preSum(j + 1, k - 1) = preSum(4, 4) = 1
preSum(k + 1, n - 1) = preSum(6, 6) = 1
Note:
1 <= n <= 2000.
Elements in the given array will be in range [-1,000,000, 1,000,000].
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
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n < 7) {
            return false;
        }

        vector<int> preSum(n, 0);
        preSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            preSum[i] = nums[i] + preSum[i - 1];
        }

        for (int j = 3; j < n - 3; j++) {
            unordered_set<int> sub;
            for (int i = 1; i < j - 1; i++) {
                if (preSum[i - 1] == preSum[j - 1] - preSum[i]) {
                    sub.insert(preSum[i - 1]);
                }
            }
            for (int k = j + 2; k < n - 1; k++) {
                if (preSum[k - 1] - preSum[j] == preSum[n - 1] - preSum[k] and
                    sub.find(preSum[k - 1] - preSum[j]) != sub.end()) {
                    return true;
                }
            }
        }
        return false;
    }
};