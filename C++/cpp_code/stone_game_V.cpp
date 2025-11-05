/*
1563. Stone Game V
https://leetcode.com/problems/stone-game-v/

There are several stones arranged in a row,
and each stone has an associated value which is an integer given in the array stoneValue.

In each round of the game, Alice divides the row into two non-empty rows
(i.e. left row and right row),
then Bob calculates the value of each row which is the sum of the values of all the stones in this row.
Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row.
If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away.
The next round starts with the remaining row.

The game ends when there is only one stone remaining.
Alice's is initially zero.
Return the maximum score that Alice can obtain.

Example 1:
Input: stoneValue = [6,2,3,4,5,5]
Output: 18
Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.

Example 2:
Input: stoneValue = [7,7,7,7,7,7,7]
Output: 28

Example 3:
Input: stoneValue = [4]
Output: 0

Constraints:
1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 10^6
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
#include <cfloat>
#include <stdio.h>
#include <map>
using namespace std;
/*
We can simply do what's stated in the question and try all the possible partitions.
If the sum of left row is less recur on the left row.
If the sum of right row is less recur on the right row.
If the sum of both rows are equal we try recuring on both the partitions and chose the one with maximum result.
Now simply repeat the steps for the new row
Do this until there is only 1 stone left.
We can see that there are recalculations of selected row when we perform the previous 3 steps. Thus we memoize on the row represented by i,j i.e row start and row end.
*/
class Solution {
private:
    vector<int> prefixSum;
    vector<vector<int> > memo;

    int dp(vector<int> &stoneValue, int i, int j) {
        if (i == j) {
            return 0;
        }

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        memo[i][j] = 0;
        for (int p = i + 1; p <= j; p++) {
            int l = prefixSum[p] - prefixSum[i];
            int r = prefixSum[j + 1] - prefixSum[p];
            if (l < r) {
                // Left part is smaller
                memo[i][j] = max(memo[i][j], l + dp(stoneValue, i, p - 1));
            } else if (l > r) {
                // Right part is smaller
                memo[i][j] = max(memo[i][j], r + dp(stoneValue, p, j));
            } else {
                // Both parts are equal
                memo[i][j] = max(memo[i][j], l + max(dp(stoneValue, p, j), dp(stoneValue, i, p - 1)));
            }
        }
        return memo[i][j];
    }

public:
    int stoneGameV(vector<int> &stoneValue) {
        int n = stoneValue.size();
        memo.resize(n, vector<int>(n, -1));
        prefixSum.resize(n + 1, 0);
        for (int i = 0; i < stoneValue.size(); i++) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }
        return dp(stoneValue, 0, n - 1);
    }
};