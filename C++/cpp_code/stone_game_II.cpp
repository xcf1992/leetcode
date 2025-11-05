/*
1140. Stone Game II
https://leetcode.com/problems/stone-game-ii/

Alex and Lee continue their games with piles of stones.
There are a number of piles arranged in a row,
and each pile has a positive integer number of stones piles[i].
The objective of the game is to end with the most stones.

Alex and Lee take turns, with Alex starting first.
Initially, M = 1.

On each player's turn,
that player can take all the stones in the first X remaining piles,
where 1 <= X <= 2M.
Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alex and Lee play optimally,
return the maximum number of stones Alex can get.

Example 1:
Input: piles = [2,7,9,4,4]
Output: 10
Explanation:
If Alex takes one pile at the beginning,
Lee takes two piles, then Alex takes 2 piles again.
Alex can get 2 + 4 + 4 = 10 piles in total.
If Alex takes two piles at the beginning,
then Lee can take all three piles left.
In this case, Alex get 2 + 7 = 9 piles in total.
So we return 10 since it's larger.

Constraints:
1 <= piles.length <= 100
1 <= piles[i] <= 10 ^ 4
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
using namespace std;

class Solution {
private:
    int n = 0;

    int getMaxStone(vector<vector<int> > &dp, vector<int> &preSum, int start, int M) {
        if (start >= n) {
            return 0;
        }

        int total = preSum[n] - preSum[start];
        if (start + 2 * M >= n) {
            return total;
        }

        if (dp[start][M] != INT_MIN) {
            return dp[start][M];
        }

        int stones = total;
        for (int x = 1; x <= 2 * M; ++x) {
            stones = min(stones, getMaxStone(dp, preSum, start + x, max(M, x)));
        }
        dp[start][M] = total - stones;
        return dp[start][M];
    }

public:
    int stoneGameII(vector<int> &piles) {
        n = piles.size();
        if (n == 0) {
            return 0;
        }

        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            preSum[i + 1] = piles[i] + preSum[i];
        }

        /*
        * dp[i][j]
        * the max stones the first player can get
        * start with stone[i] (0-based), and with M = j
        */
        vector<vector<int> > dp(n, vector<int>(2 * n, INT_MIN));
        return getMaxStone(dp, preSum, 0, 1);
    }
};