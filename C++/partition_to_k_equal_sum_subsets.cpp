/*
698. Partition to K Equal Sum Subsets
Given an array of integers nums and a positive integer k,
find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.


Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.
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
#include <numeric>
#include <map>
using namespace std;

class Solution { // dp O(N * 2 ^ N)
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int N = nums.size();
        sort(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int target = sum / k;
        if (sum % k > 0 or nums[N - 1] > target) {
            return false;
        }

        vector<bool> dp(1 << N, false);
        dp[0] = true;
        vector<int> total(1 << N, 0);
        for (int state = 0; state < (1 << N); state++) {
            if (!dp[state]) {
                continue;
            }
            for (int i = 0; i < N; i++) {
                int future = state | (1 << i);
                if (state != future and !dp[future]) {
                    if (nums[i] <= target - (total[state] % target)) {
                        dp[future] = true;
                        total[future] = total[state] + nums[i];
                    } else {
                        break;
                    }
                }
            }
        }
        return dp[(1 << N) - 1];
    }
};

class Solution1 {
private:
    bool partition(vector<int>& nums, vector<int>& used, int start, int k, int curSum, int target) {
        if (k == 0) {
            return true;
        }

        if (curSum == target) {
            return partition(nums, used, 0, k - 1, 0, target);
        }
        for (int i = start; i < nums.size(); i++) {
            if (!used[i] and curSum + nums[i] <= target) {
                used[i] = true;
                if (partition(nums, used, i + 1, k, curSum + nums[i], target)) {
                    return true;
                }
                used[i] = false;
            }
        }
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return false;
        }
        vector<int> used(nums.size(), false);
        return partition(nums, used, 0, k, 0, sum / k);
    }
};
