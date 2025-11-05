/*
1223. Dice Roll Simulation
https://leetcode.com/problems/dice-roll-simulation/

A die simulator generates a random number from 1 to 6 for each roll.
You introduced a constraint to the generator
such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.

Given an array of integers rollMax and an integer n,
return the number of distinct sequences that can be obtained with exact n rolls.

Two sequences are considered different if at least one element differs from each other.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 2, rollMax = [1,1,2,2,2,3]
Output: 34
Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.

Example 2:
Input: n = 2, rollMax = [1,1,1,1,1,1]
Output: 30

Example 3:
Input: n = 3, rollMax = [1,1,1,2,2,3]
Output: 181

Constraints:
1 <= n <= 5000
rollMax.length == 6
1 <= rollMax[i] <= 15
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

class Solution {
    // dfs with memo
private:
    int mod = 1e9 + 7;

    int dfs(int n, int preNum, int preCount, vector<vector<vector<int> > > &memo, vector<int> &rollMax) {
        if (n == 0) {
            return 1;
        }

        if (preNum != -1 and memo[n][preCount][preNum]
        !=
        0
        )
        {
            return memo[n][preCount][preNum];
        }

        int count = 0;
        for (int cur = 0; cur < 6; ++cur) {
            if (cur == preNum and preCount
            +1 > rollMax[preNum]
            )
            {
                continue;
            }
            count = (count + dfs(n - 1, cur, cur == preNum ? preCount + 1 : 1, memo, rollMax)) % mod;
        }

        if (preNum != -1) {
            memo[n][preCount][preNum] = count;
        }
        return count;
    }

public:
    int dieSimulator(int n, vector<int> &rollMax) {
        vector<vector<vector<int> > > memo(n + 1, vector<vector<int> >(16, vector<int>(6, 0)));
        return dfs(n, -1, 0, memo, rollMax);
    }
};