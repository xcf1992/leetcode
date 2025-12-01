/*
https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/description/
3578. Count Partitions With Max-Min Difference at Most K

You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty
contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.

Return the total number of ways to partition nums under this condition.

Since the answer may be too large, return it modulo 109 + 7.



Example 1:

Input: nums = [9,4,1,3,7], k = 4

Output: 6

Explanation:

There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k
= 4:

[[9], [4], [1], [3], [7]]
[[9], [4], [1], [3, 7]]
[[9], [4], [1, 3], [7]]
[[9], [4, 1], [3], [7]]
[[9], [4, 1], [3, 7]]
[[9], [4, 1, 3], [7]]
Example 2:

Input: nums = [3,3,4], k = 0

Output: 2

Explanation:

There are 2 valid partitions that satisfy the given conditions:

[[3], [3], [4]]
[[3, 3], [4]]


Constraints:

2 <= nums.length <= 5 * 104
1 <= nums[i] <= 109
0 <= k <= 109
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

/*
We use dp[i] to count the number of ways to partition the first i elements.

At each index j, we find the earliest i such that A[i..j] has max - min ≤ k.
All valid partitions ending at j can be formed by adding A[i..j] to partitions ending before i.

We use acc to get the total dp[i..j] range in O(1), and two deques to maintain the min and max in the sliding window.

Finally, dp[n] gives the total number of valid partitions.
 */
class Solution {
private:
    int mod = 1e9 + 7;

public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        deque<int> min_q;
        deque<int> max_q;
        int pre_sum = 1;  // pre_sum of dp vector
        for (int left = 0, right = 0; right < n; right++) {
            while (!max_q.empty() && nums[right] > nums[max_q.back()]) {
                max_q.pop_back();
            }
            max_q.push_back(right);

            while (!min_q.empty() && nums[right] < nums[min_q.back()]) {
                min_q.pop_back();
            }
            min_q.push_back(right);

            while (nums[max_q.front()] - nums[min_q.front()] > k) {
                pre_sum = (pre_sum - dp[left] + mod) % mod;
                left += 1;
                if (min_q.front() < left) {
                    min_q.pop_front();
                }
                if (max_q.front() < left) {
                    max_q.pop_front();
                }
            }

            dp[right + 1] = pre_sum;
            pre_sum = (pre_sum + dp[right + 1]) % mod;
        }
        return dp[n];
    }
};

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        long long mod = 1e9 + 7;
        vector<long long> dp(n + 1); // dp[i] is the valid cnt using nums[0...i - 1]; end at nums[i - 1]
        vector<long long> pre_sum(n + 1); // pre_sum[i] is dp[0...i]; end at nums[i - 1]
        multiset<int> window;
        dp[0] = 1;
        pre_sum[0] = 1;
        for (int right = 0, left = 0; right < nums.size(); right++) {
            window.insert(nums[right]);
            while (left <= right && *window.rbegin() - *window.begin() > k) {
                window.erase(window.find(nums[left]));
                left += 1;
            }
            dp[right + 1] = (pre_sum[right] - (left > 0 ? pre_sum[left - 1] : 0) + mod) % mod;
            pre_sum[right + 1] = (pre_sum[right] + dp[right + 1]) % mod;
        }
        return dp[n];
    }
};
