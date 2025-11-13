/*
https://leetcode.com/problems/maximize-win-from-two-segments/description/
2555. Maximize Win From Two Segments

There are some prizes on the X-axis. You are given an integer array prizePositions that is sorted in non-decreasing
order, where prizePositions[i] is the position of the ith prize. There could be different prizes at the same position on
the line. You are also given an integer k.

You are allowed to select two segments with integer endpoints. The length of each segment must be k. You will collect
all prizes whose position falls within at least one of the two selected segments (including the endpoints of the
segments). The two selected segments may intersect.

For example if k = 2, you can choose segments [1, 3] and [2, 4], and you will win any prize i that satisfies 1 <=
prizePositions[i] <= 3 or 2 <= prizePositions[i] <= 4. Return the maximum number of prizes you can win if you choose the
two segments optimally.



Example 1:

Input: prizePositions = [1,1,2,2,3,3,5], k = 2
Output: 7
Explanation: In this example, you can win all 7 prizes by selecting two segments [1, 3] and [3, 5].
Example 2:

Input: prizePositions = [1,2,3,4], k = 0
Output: 2
Explanation: For this example, one choice for the segments is [3, 3] and [4, 4], and you will be able to get 2 prizes.


Constraints:

1 <= prizePositions.length <= 105
1 <= prizePositions[i] <= 109
0 <= k <= 109
prizePositions is sorted in non-decreasing order.
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
Intuition
Maximize Win From One Segments,
can be solved by sliding window.

Now we can slide the second segment,
and get calculate the result from dp.


Explanation
Maintain a sliding segment(sliding window),
where A[i] - A[j] <= k.

dp[k] means the the maximum number
we can cover if you choose the one segments optimally
in the first k elements.

When we slide a segment from left to right,
the number of elements that we cover is i - j + 1
and in the first j elements,
we can cover at most dp[j] elements,
so we can cover i - j + 1 + dp[j] in total.
Update the result res and finally return it.
 */
class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        vector<int> dp(n + 1, 0);
        int left_idx = 0;
        int right_idx = 0;
        int rst = 0;
        while (right_idx < n) {
            while (prizePositions[right_idx] - prizePositions[left_idx] > k) {
                left_idx += 1;
            }

            dp[right_idx + 1] = max(dp[right_idx], right_idx - left_idx + 1); // optimal cnt for one segment
            rst = max(rst, dp[left_idx] + right_idx - left_idx + 1);
            right_idx += 1;
        }
        return rst;
    }
};