/*
956. Tallest Billboard

You are installing a billboard and want it to have the largest height.
The billboard will have two steel supports, one on each side.
Each steel support must be an equal height.

You have a collection of rods which can be welded together.
For example, if you have rods of lengths 1, 2, and 3,
you can weld them together to make a support of length 6.

Return the largest possible height of your billboard installation.
If you cannot support the billboard, return 0.

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
Explanation:
dp[d] mean the maximum pair of sum we can get with pair difference d
For example, if have a pair of sum (a, b) with a > b, then dp[a - b] = b
If we have dp[diff] = a, it means we have a pair of sum (a, a + diff).
And this is the biggest pair with difference = a

dp is initializes with dp[0] = 0;

Assume we have an init state like this
------- y ------|----- d -----|
------- y ------|

case 1
If put x to tall side
------- y ------|----- d -----|----- x -----|
------- y ------|

We update dp[d + x] = max(dp[d + x], y )

case 2.1
Put x to low side and d >= x:
-------y------|----- d -----|
-------y------|--- x ---|

We update dp[d-x] = max( dp[d - x], y + x)

case 2.2
Put x to low side and d < x:
------- y ------|----- d -----|
------- y ------|------- x -------|
We update dp[x - d] = max(dp[x - d], y + d)

case 2.1 and case2.2 can merge into dp[abs(x - d)] = max(dp[abs(x - d)], y + min(d, x))


Time Complexity:
O(NM), where we have
N = rod.length <= 20
S = sum(rods) <= 5000
M = all possible sum = min(3^N, S)

There are 3 ways to arrange a number: in the first group, in the second, not used.
The number of difference will be less than 3^N.
The only case to reach 3^N is when rod = [1,3,9,27,81...]
*/
class Solution1 {
public:
    int tallestBillboard(vector<int> &rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;
        for (int height: rods) {
            unordered_map<int, int> cur(dp);
            for (auto &it: cur) {
                int diff = it.first;
                dp[diff + height] = max(dp[diff + height], cur[diff]);
                dp[abs(diff - height)] = max(dp[abs(diff - height)], cur[diff] + min(diff, height));
            }
        }
        return dp[0];
    }
};

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
Thus, dp[i][j] comes from dp[i-1][j+rods[i]], the length of bag1 remains still. so is still dp[i - 1][j+rods[i]]

we add rods[i] to bag0 and bag0 is now longer than bag1.
We have current bag1 - bag0 = j; and previously, bag0 - (bag1 - rod[i]) = x
so we can get x = rod[i] - j; As previously, bag0 = dp[i-1][rods[i]-j], and it is now j less than current bag1
Thus, dp[i][j] comes from dp[i-1][rods[i]-j], dp[i][j] = dp[i-1][rods[i]-j]+j

After all, just output dp[n][0].
*/
class Solution {
private:
    int maxLength = 5000; // as the sum could be at most 5000
public:
    int tallestBillboard(vector<int> &rods) {
        int n = rods.size();
        vector<vector<int> > dp(n + 1, vector<int>(maxLength + 1));
        for (int diff = 0; diff < maxLength; diff++) {
            dp[0][diff] = INT_MIN;
        }
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int diff = 0; diff <= maxLength; diff++) {
                if (diff >= rods[i - 1]) {
                    // the order of bag0 and bag1 does not change
                    dp[i][diff] = max(dp[i - 1][diff + rods[i - 1]], dp[i - 1][diff - rods[i - 1]] + rods[i - 1]);
                } else {
                    dp[i][diff] = max(dp[i - 1][diff + rods[i - 1]], dp[i - 1][rods[i - 1] - diff] + diff);
                }
                dp[i][diff] = max(dp[i][diff], dp[i - 1][diff]); // we could choose not to use rods[i - 1]
            }
        }
        return dp[n][0];
    }
};