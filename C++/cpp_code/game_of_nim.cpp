/*
https://leetcode.com/problems/game-of-nim/description/
1908. Game of Nim

Alice and Bob take turns playing a game with Alice starting first.

In this game, there are n piles of stones. On each player's turn, the player should remove any positive number of stones
from a non-empty pile of his or her choice. The first player who cannot make a move loses, and the other player wins.

Given an integer array piles, where piles[i] is the number of stones in the ith pile, return true if Alice wins, or
false if Bob wins.

Both Alice and Bob play optimally.



Example 1:

Input: piles = [1]
Output: true
Explanation: There is only one possible scenario:
- On the first turn, Alice removes one stone from the first pile. piles = [0].
- On the second turn, there are no stones left for Bob to remove. Alice wins.
Example 2:

Input: piles = [1,1]
Output: false
Explanation: It can be proven that Bob will always win. One possible scenario is:
- On the first turn, Alice removes one stone from the first pile. piles = [0,1].
- On the second turn, Bob removes one stone from the second pile. piles = [0,0].
- On the third turn, there are no stones left for Alice to remove. Bob wins.
Example 3:

Input: piles = [1,2,3]
Output: false
Explanation: It can be proven that Bob will always win. One possible scenario is:
- On the first turn, Alice removes three stones from the third pile. piles = [1,2,0].
- On the second turn, Bob removes one stone from the second pile. piles = [1,1,0].
- On the third turn, Alice removes one stone from the first pile. piles = [0,1,0].
- On the fourth turn, Bob removes one stone from the second pile. piles = [0,0,0].
- On the fifth turn, there are no stones left for Alice to remove. Bob wins.


Constraints:

n == piles.length
1 <= n <= 7
1 <= piles[i] <= 7


Follow-up: Could you find a linear time solution? Although the linear time solution may be beyond the scope of an
interview, it could be interesting to know.
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

class Solution {
private:
    int get_mask(vector<int>& piles) {
        int mask = 0;
        for (int i = 0; i < piles.size(); i++) {
            mask |= piles[i] << (3 * i);
        }
        return mask;
    }

    bool solve(unordered_map<int, bool>& dp, int n, int mask) {

        if (dp.find(mask) != dp.end()) {
            return dp[mask];
        }

        dp[mask] = false;
        for (int i = 0; i < n; i++) {
            int pile_cnt = (mask >> (i * 3)) & 7;
            for (int pick = 1; pick <= pile_cnt; pick++) {
                int new_mask = mask - (pick << (3 * i));
                if (!solve(dp, n, new_mask)) {
                    dp[mask] = true;
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool nimGame(vector<int>& piles) {
        int n = piles.size();
        int mask = get_mask(piles);
        unordered_map<int, bool> dp;
        return solve(dp, n, mask);
    }
};

class Solution {
public:
    bool nimGame(vector<int>& piles) {
        int ans = 0;
        for (auto& x : piles) ans ^= x;
        return ans;
    }
};
