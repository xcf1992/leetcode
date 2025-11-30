/*
1824. Minimum Sideway Jumps
https://leetcode.com/problems/minimum-sideway-jumps/

There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n.
A frog starts at point 0 in the second lane and wants to jump to point n.
However, there could be obstacles along the way.

You are given an array obstacles of length n + 1 where each obstacles[i]
(ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i.
If obstacles[i] == 0, there are no obstacles at point i.
There will be at most one obstacle in the 3 lanes at each point.

For example, if obstacles[2] == 1,
then there is an obstacle on lane 1 at point 2.
The frog can only travel from point i to point i + 1 on the same lane
if there is not an obstacle on the lane at point i + 1.
To avoid obstacles,
the frog can also perform a side jump to jump to another lane
(even if they are not adjacent) at the same point if there is no obstacle on the new lane.

For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.

Note: There will be no obstacles on points 0 and n.

Example 1:
Input: obstacles = [0,1,2,3,0]
Output: 2
Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
Example 2:
Input: obstacles = [0,1,1,3,3,0]
Output: 0
Explanation: There are no obstacles on lane 2. No side jumps are required.
Example 3:
Input: obstacles = [0,2,1,0,3,0]
Output: 2
Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps.

Constraints:
obstacles.length == n + 1
1 <= n <= 5 * 105
0 <= obstacles[i] <= 3
obstacles[0] == obstacles[n] == 0
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
dp[0] = minimum jump to reach lane 1
dp[1] = minimum jump to reach lane 2
dp[2] = minimum jump to reach lane 3
If meet a stone, set its dp[i] to infinity.
result equals to min(dp)
*/
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int dp[] = {1, 0, 1};
        for (int ob_lane : obstacles) {
            if (ob_lane > 0) {
                dp[ob_lane - 1] = 1e6;
            }

            for (int i = 0; i < 3; ++i) {
                if (ob_lane != i + 1) {
                    dp[i] = min(dp[i], min(dp[(i + 1) % 3], dp[(i + 2) % 3]) + 1);
                }
            }
        }
        return min(dp[0], min(dp[1], dp[2]));
    }
};

/*
We can use DP to solve this problem. dp[i][r] means the minimum jumps when the frog gets to point i lane r (0-index).

The base cases are:

dp[0][0], dp[0][1], dp[0][2] = 1, 0, 1
dp[i][r] = inf when there's obstacle at (i, r) or (i+1, r)
And the transition function is:

dp[i][r] = min([dp[i-1][r], dp[i-1][(r+1)%3] + 1, dp[i-1][(r+2)%3] + 1]) for r = 0, 1, 2
dp[i-1][r] means the frog comes from the same lane, so there's no jump needed; otherwise, the frog moves from point i-1
to point i on another lane and jumps to (i, r).


Complexity

Time complexity: O(N)
Space complexity: O(N) or O(1) if we use rolling array
 */

class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        vector<int> dp({1,0,1});
        for (int ob : obstacles) {
            vector<int> temp(3, 0);
            int ob_idx = ob - 1;
            if (ob_idx == -1) { // no stone
                temp[0] = min(dp[0], min(dp[1] + 1, dp[2] + 1));
                temp[1] = min(dp[1], min(dp[0] + 1, dp[2] + 1));
                temp[2] = min(dp[2], min(dp[0] + 1, dp[1] + 1));
            }

            if (ob_idx == 0) {
                temp[0] = 1e6;
                temp[1] = min(dp[1], dp[2] + 1);
                temp[2] = min(dp[2], dp[1] + 1);
            }

            if (ob_idx == 1) {
                temp[0] = min(dp[0], dp[2] + 1);
                temp[1] = 1e6;
                temp[2] = min(dp[2], dp[0] + 1);
            }

            if (ob_idx == 2) {
                temp[0] = min(dp[0], dp[1] + 1);
                temp[1] = min(dp[1], dp[0] + 1);
                temp[2] = 1e6;
            }
            dp = temp;
        }
        return *min_element(dp.begin(), dp.end());
    }
};