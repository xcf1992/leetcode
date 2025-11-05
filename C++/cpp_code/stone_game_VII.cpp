/*
1690. Stone Game VII
https://leetcode.com/problems/stone-game-vii/

Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row.
On each player's turn, they can remove either the leftmost stone
or the rightmost stone from the row
and receive points equal to the sum of the remaining stones' values in the row.
The winner is the one with the higher score when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses),
so he decided to minimize the score's difference.
Alice's goal is to maximize the difference in the score.

Given an array of integers stones where stones[i] represents the value of the ith stone from the left,
return the difference in Alice and Bob's score if they both play optimally.

Example 1:
Input: stones = [5,3,1,4,2]
Output: 6
Explanation:
- Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
- Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
- Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
- Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
- Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
The score difference is 18 - 12 = 6.

Example 2:
Input: stones = [7,90,5,1,100,10,10,2]
Output: 122

Constraints:
n == stones.length
2 <= n <= 1000
1 <= stones[i] <= 1000
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
Let dp[i][j] be the maximum difference the first player can get if the players play on A[i..j].

dp[i][j] = max(
                sum(i + 1, j) - dp[i + 1][j],   // if the first player choose `A[i]`
                sum(i, j - 1) - dp[i][j - 1]    // if the first player choose `A[j]`
              )
where sum(i, j) is A[i] + ... + A[j]. We can get sum(i, j) using prefix sum array.

Let say, if it's our turn on [i,j] and we took stones[i],
we will add to our scores an amount of amount = sum[j + 1] - sum[i + 1].
In the next turn [i+1,j],
the next player will play optimally
and get an optimal score difference dp[i+1][j] = his_scores - my_scores.
So, in the interval [i,j],
the new difference will be dp[i][j] = my_scores + amount - his_scores,
that can be write as dp[i][j] = amount - (his_scores - my_scores).
That is dp[i][j] = sums[j+1] - sums[i+1] - dp[i+1][j]
if we took stones[i].
*/
class Solution {
public:
    int stoneGameVII(vector<int> &A) {
        int N = A.size();
        vector<int> sum(N + 1);
        for (int i = 0; i < N; ++i) sum[i + 1] = sum[i] + A[i];
        vector<vector<int> > dp(N, vector<int>(N));
        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i <= N - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = max(sum[j + 1] - sum[i + 1] - dp[i + 1][j], sum[j] - sum[i] - dp[i][j - 1]);
            }
        }
        return dp[0][N - 1];
    }
};