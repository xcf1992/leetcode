/*
 375. Guess Number Higher or Lower II
 We are playing the Guess Game. The game is as follows:

 I pick a number from 1 to n. You have to guess which number I picked.

 Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

 However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

 Example:

 n = 10, I pick 8.

 First round:  You guess 5, I tell you that it's higher. You pay $5.
 Second round: You guess 7, I tell you that it's higher. You pay $7.
 Third round:  You guess 9, I tell you that it's lower. You pay $9.

 Game over. 8 is the number I picked.

 You end up paying $5 + $7 + $9 = $21.
 Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
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
#include <set>
using namespace std;

/*
 For each number x in range[i~j]
 we do: result_when_pick_x = x + max{DP([i~x-1]), DP([x+1, j])}
 –> // the max means whenever you choose a number, the feedback is always bad and therefore leads you to a worse branch.
 then we get DP([i~j]) = min{xi, … ,xj}
 –> // this min makes sure that you are minimizing your cost.

 It takes me some time to understand the simple question “why it’s using max(dp[i][x-1], dp[x+1][j])”, so I want to share my understanding here to help people like me.

 dp[i][j] is the minimal cost to guess from range(i…j).
 When you choose an x where i <= x <= j, you may find the target number from left i…x-1, or you may find the target number from the x+1…j,
 because you don’t know which way should go, so to guarantee you have enough money to find the target, you need to prepare the more, which is max(dp[i][x-1], dp[x+1][j]).
 */
class Solution {
private:
    int calculate(int start, int end, vector<vector<int>>& dp) {
        if (start >= end) {
            return 0;
        }

        if (dp[start][end] != 0) {
            return dp[start][end];
        }

        int result = INT_MAX;
        for (int guess = start; guess <= end; guess++) {
            result = min(result, guess + max(calculate(start, guess - 1, dp), calculate(guess + 1, end, dp)));
        }
        dp[start][end] = result;
        return result;
    }
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        return calculate(1, n, dp);
    }
};
