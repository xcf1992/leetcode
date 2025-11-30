/*
1681. Minimum Incompatibility
https://leetcode.com/problems/minimum-incompatibility/

You are given an integer array nums​​​ and an integer k.
You are asked to distribute this array into k subsets
of equal size such that there are no two equal elements in the same subset.

A subset's incompatibility is the difference between the maximum and minimum elements in that array.
Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally,
or return -1 if it is not possible.

A subset is a group integers that appear in the array with no particular order.

Example 1:
Input: nums = [1,2,1,4], k = 2
Output: 4
Explanation: The optimal distribution of subsets is [1,2] and [1,4].
The incompatibility is (2-1) + (4-1) = 4.
Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.

Example 2:
Input: nums = [6,3,8,1,3,1,2,2], k = 4
Output: 6
Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8], and [1,3].
The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.

Example 3:
Input: nums = [5,3,3,6,3,3], k = 3
Output: -1
Explanation: It is impossible to distribute nums into 3 subsets where no two elements are equal in the same subset.

Constraints:
1 <= k <= nums.length <= 16
nums.length is divisible by k
1 <= nums[i] <= nums.length
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
#include <numeric>
using namespace std;
/*
Since n is at most 16, we can use a bitmap to represent any subset of the input array.
Define dp[b] as the answer to the subset represented by bitmap b,
we can iterate over all the valid subset tb of b of size n/k, and update dp[b] as min(dp[b], dp[b-tb]+dp[tb]).

To speed up the inner loop, we can pre-generate all the valid subsets of size n/k and corresponding incompatibilities.
*/
class Solution {
private:
    // Generates a vetor v where:
    //   v[b] = the incompatibility of bitmask b, if b represents a valid subset of size m
    //   v[b] = -1, if b is not a valid subset of size m
    vector<int> getMap(const vector<int>& nums, int m) {
        const int n = nums.size();
        vector<int> ans(1 << n, -1);
        for (int b = 0; b < (1 << n); ++b) {
            if (__builtin_popcount(b) != m)
                continue;

            int vis = 0;
            int mx = 0, mn = 16;
            bool is_good = true;
            for (int i = 0; i < n; ++i) {
                if ((b & (1 << i)) == 0)
                    continue;
                if (vis & (1 << nums[i])) {
                    is_good = false;
                    break;
                }
                vis |= (1 << nums[i]);
                mx = max(mx, nums[i]);
                mn = min(mn, nums[i]);
            }
            if (!is_good)
                continue;

            ans[b] = mx - mn;
        }
        return ans;
    }

public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        const int n = nums.size(), m = n / k;
        const vector<int> bmap = getMap(nums, m);

        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int b = 0; b < (1 << n); ++b) {
            if (__builtin_popcount(b) % m != 0)
                continue;
            // Reference: https://cp-algorithms.com/algebra/all-submasks.html
            for (int tb = b; tb; tb = (tb - 1) & b) {
                if (bmap[tb] == -1)
                    continue;
                if (dp[b - tb] == -1)
                    continue;
                if (dp[b] == -1)
                    dp[b] = dp[b - tb] + bmap[tb];
                else
                    dp[b] = min(dp[b], dp[b - tb] + bmap[tb]);
            }
        }
        return dp.back();
    }
};