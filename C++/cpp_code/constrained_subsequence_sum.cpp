/*
1425. Constrained Subsequence Sum
https://leetcode.com/problems/constrained-subsequence-sum/

Given an integer array nums and an integer k,
return the maximum sum of a non-empty subsequence of that array
such that for every two consecutive integers in the subsequence,
nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array,
leaving the remaining elements in their original order.

Example 1:
Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].

Example 2:
Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.

Example 3:
Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].

Constraints:
1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
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
#include <set>
using namespace std;
/*
Intuition
We need to know the maximum in the window of size k.
Use heqp will be O(NlogN)
Use TreeMap will be O(NlogK)
Use deque will be O(N)
Done. (If not done, continue read)

Prepare
How about google "sliding window maximum",
and make sure you understand 239. Sliding Window Maximum
Done. (If not done, continue read)

Explanation
Update res[i],
where res[i] means the maximum result you can get if the last element is A[i].

I directly modify on the input A,
if you don't like it,
use a copy of A

Keep a decreasing deque q,
deque[0] is the maximum result in the last element of result.

If deque[0] > 0. we add it to A[i]

In the end, we return the maximum res.


Complexity
Because all element are pushed and popped at most once.
Time O(N)

Because at most O(K) elements in the deque.
Space O(K)


More
Deque can be widely used in all bfs problems.
For more complecated usage,
I recall this problem
862. Shortest Subarray with Sum at Least K

 Transition: A[i] = max(0, A[i - k], A[i - k + 1], .., A[i - 1]) + A[i]. (@lee215 modifies the input A directly)
        Translated into a traditional dp: dp[i] = max(0, dp[i - k], dp[i - k + 1], .., dp[i -1]) + A[i]
        dp[i] is the max sum we can have from A[:i] when A[i] has been chosen.
        """
        # `deque` stores dp[i - k], dp[i-k+1], .., dp[i - 1] whose values are larger than 0 in a decreasing order
        # Note that the length of `deque` is not necessarily `k`. The values smaller than dp[i-1] will be discarded.
 1. We always want to retrieve the max of (0, dp[i - k], dp[i-k+1], .., dp[i - 1]) from `deque`
            # 2. We expect dp[i] to be added to `deque` so that we can compute dp[i + 1] in the next iteration
            # 3. So, if dp[i] is larger than some old values, we can discard them safely.
            # 4. As a result, the length of `deque` is not necessarily `k`

we do not need the value of A[i - k] when computing dp[i+1] in the next iteration, because `j - i <= k` has to be
satisfied.
*/
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        deque<int> subsequency_sum;
        int rst = nums[0];
        for (int i = 0; i < nums.size(); ++i) {
            nums[i] += !subsequency_sum.empty() ? subsequency_sum.front() : 0;
            rst = max(rst, nums[i]);

            while (!subsequency_sum.empty() && nums[i] > subsequency_sum.back()) {
                subsequency_sum.pop_back();
            }

            if (nums[i] > 0) {
                subsequency_sum.push_back(nums[i]);
            }

            if (i >= k && !subsequency_sum.empty() && subsequency_sum.front() == nums[i - k]) {
                subsequency_sum.pop_front();
            }
        }
        return rst;
    }
};