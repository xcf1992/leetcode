/*
 You are installing a billboard and want it to have the largest height.  The billboard will have two steel supports, one on each side.  Each steel support must be an equal height.

 You have a collection of rods which can be welded together.  For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.

 Return the largest possible height of your billboard installation.  If you cannot support the billboard, return 0.



 Example 1:

 Input: [1,2,3,6]
 Output: 6
 Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
 Example 2:

 Input: [1,2,3,4,5,6]
 Output: 10
 Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.
 Example 3:

 Input: [1,2]
 Output: 0
 Explanation: The billboard cannot be supported, so we return 0.


 Note:

 0 <= rods.length <= 20
 1 <= rods[i] <= 1000
 The sum of rods is at most 5000.
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
#include <map>
#include <numeric>
using namespace std;

/*
 dp[i][j] represents the maximum total length in bag1 when puting some of the first i rods into two bags, bag0 and bag1,
 where bag0 is always smaller than or equal to bag1, and the difference of bag0 and bag1 is j,
 which means total length of bag1 is j longer than bag0.

 Say dp[i][j] = x; then length of bag1 is x, the length difference between bag1 and bag0 is j
 so the length of bag0 is x - j

 There are three situations:
 we add rods[i] to bag1,
 thus dp[i][j] comes from dp[i-1][j-rods[i]] and the total length of current result should be dp[i-1][j-rods[i]]+rods[i]
 as we add rod[i] to bag 1

 we add rods[i] to bag0 and bag0 is still shorter than bag1.
 Thus, dp[i][j] comes from dp[i-1][j+rods[i]], the length of bag1 remains still. so is still dp[i - 1][diff]

 we add rods[i] to bag0 and bag0 is now longer than bag1.
 We have current bag1 - bag0 = j; and previously bag0 - (bag1 - rod[i]) = x
 so we can get x = rod[i] - j; As previously bag0 = dp[i-1][rods[i]-j], and it is now j less than current bag1
 Thus, dp[i][j] comes from dp[i-1][rods[i]-j], dp[i][j] = dp[i-1][rods[i]-j]+j

 After all, just output dp[n][0].
 */
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        int maxLength = 5000; // as the sum could be at most 5000
        vector<vector<int>> dp(n + 1, vector<int>(maxLength + 1));
        for (int diff = 0; diff < maxLength; diff++) {
            dp[0][diff] = INT_MIN;
        }
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int diff = 0; diff <= maxLength; diff++) {
                if (diff >= rods[i - 1]) { // the order of bag0 and bag1 does not change
                    dp[i][diff] = max(dp[i - 1][diff + rods[i - 1]], dp[i - 1][diff - rods[i - 1]] + rods[i - 1]);
                }
                else {
                    dp[i][diff] = max(dp[i - 1][diff + rods[i - 1]], dp[i - 1][rods[i - 1] - diff] + diff);
                }
                dp[i][diff] = max(dp[i][diff], dp[i - 1][diff]); // we could choose not to use rods[i - 1]
            }
        }
        return dp[n][0];
    }
};
