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

/*
Intuition
The nim game is a classical problem. Its solution has existed for a long time. The theory upon which the current
approach is based was presented by Charles Bouton in 1901. While we can prove that the theory works, developing an
intuition for it takes work. After reading the proceeding section, it is absolutely fine if you see yourself as unable
to come up with intuition. Although in contrast, the implementation is equally easy. We recommend trying this approach
here but suggest using the recursion-based approach for an interview setting.

The optimal strategy to win the nim game is based on the bitwise XOR sum of all the stacks. Let's take an example. Say
we have three stacks of stones with 3, 2, and 5 stones in them. We can express 3 in base 2 as 11
2
​
 , 2 as 10
2
​
 , and 5 as 101
2
​
 . The bitwise XOR sum of all the piles, also called the nim-sum, is 11
2
​
 ⊕10
2
​
 ⊕101
2
​
 =100
2
​
 . This is the same as 4
10
​
 .

The nim-sum of a state is the key to finding the winner of the game. A game can only be in one of the two states - (1) a
state with nim-sum zero and (2) a state with nim-sum non-zero. This is similar to saying a number could either be zero
or non-zero.

If the nim-sum of the current state is not zero, then the current player makes a move so that the resulting state has a
nim-sum of zero (we can show that such a move is always available). A player from a state with zero nim-sum can only
move to a non-zero nim-sum state (in the proof below, we'll show that from a zero nim-sum state, a player can move only
to a non-zero nim-sum state). Please note that the nim-sum of the state with no stones is zero. The game continues in
this manner until all the piles have no stones left. The player who makes the last move wins the game.

This means a player who starts the game in a non-zero nim-sum state will always find themselves in a non-zero nim-sum
state after the next player's turn. And thus, will win the game. In contrast, players who start the game in a zero
nim-sum state will always find themselves in a zero nim-sum state. And thus will always lose the game (we again assume
that the players are rational).

Theorem
The winning strategy in the game of nim is to finish every move with a zero nim-sum state.

We call a state with non-zero nim-sum a winning state. And a state with zero nim-sum, a losing state.

Why does it work?

From a winning state, there is always at least one move available to reach a losing state. Similarly, from a losing
state, all the moves lead to a winning state. So, if the game starts in a winning state, the first person is also the
last to move. The game ends with the first player winning it. If the game begins in a losing state, it ends in a losing
state. Let's prove both points now.

Lemma 1: If a player is in a zero nim-sum state, they can move only to a non-zero nim-sum state.

Proof

Let's say we have a zero nim-sum state. The current player has k piles with n
1
​
 ,n
2
​
 ,…,n
k
​
  stones. The player removes x stones from the i
th
  pile. The resulting state will have k piles with n
1
​
 ,n
2
​
 ,…,n
k
​
  stones in them, except for the i
th
  pile, which will have n
i
​
 −x stones in it.

The nim-sum of the game before the move is 0 (⊕ represents XOR operation between two numbers)

n
1
​
 ⊕n
2
​
 ⊕⋯⊕n
i
​
 ⋯⊕n
k
​
 =0

this means

n
1
​
 ⊕n
2
​
 ⊕⋯⊕n
k
​
 =n
i
​


Let's say the nim-sum of the game after the move is s

n
1
​
 ⊕n
2
​
 ⊕⋯⊕(n
i
​
 −x)⊕⋯⊕n
k
​
 =s

n
i
​
 ⊕(n
i
​
 −x)=s

Recall that the XOR sum of two values can be 0 only if both are equal. So s can be zero only if both n
i
​
  and n
i
​
 −x are equal. But x is a non-zero quantity because at least one stone has to be removed from the pile. So, s is always
non-zero.

We can also see this with an example.

Let's say we have four piles with 2, 3, 4, and 5 stones. The nim-sum of the state is 2⊕3⊕4⊕5=0. If we remove a stone
from the second pile, the resulting state will have 2, 2, 4, and 5 stones. The nim-sum of the state is 2⊕2⊕4⊕5=1.
Similarly, we can try removing any number of stones from any pile, and the resulting nim-sum will always be non-zero.

Lemma 2: Moving from a non-zero nim-sum state to a zero nim-sum state is always possible.

Proof

Let's say we have a non-zero nim-sum state. The current player has k piles with n
1
​
 ,n
2
​
 ,…,n
k
​
  stones. Its nim-sum is s. We find the position of the leftmost set bit (most significant bit) in s. Now let's select a
pile n
i
​
 , which also has a set bit at the same position. Because the most significant bits in both s and n
i
​
  are set, the XOR sum y of these two numbers will be less than n
i
​
 . So, we can remove n
i
​
 −y stones from the pile n
i
​
 .

n
1
​
 ⊕n
2
​
 ⊕⋯⊕n
i
​
 ⋯⊕n
k
​
 =s

y
i
​
 =s⊕n
i
​


The new XOR sum t after making a move

n
1
​
 ⊕n
2
​
 ⊕⋯⊕y⋯⊕n
k
​
 =t

n
1
​
 ⊕n
2
​
 ⊕⋯⊕s⊕n
i
​
 ⋯⊕n
k
​
 =t

Move everything other than s

n
1
​
 ⊕n
2
​
 ⊕⋯⊕n
i
​
 ⋯⊕n
k
​
 ⊕s=t

s+s=t

t=0

This means there is always a move available to reach a zero nim-sum state.

Let's take an example to understand this.

Let's say we have three piles with 2,3, and 4 stones. The nim-sum of the state is 2⊕3⊕4=5. In base 2 representation it
is 010
2
​
 ⊕011
2
​
 ⊕100
2
​
 =101
2
​
 . The leftmost set bit of the nim-sum 101
2
​
  is at the third position from the right. So, we can select the pile with 4 (In base 2, it is 100
2
​
 ) stones in it because 100
2
​
  has its most significant bit at the same position as the nim-sum 101
2
​
 . The XOR sum of 5 and 4 is 1. So, we can remove 4−1=3 stone from the pile with 4 stones. The resulting state will have
2, 3, and 1 stones. The nim-sum of the state is 2⊕3⊕1=0.

Current


Algorithm
Initialize nimSum to 0.
Iterate over all the piles. For each pile p, update nimSum as the XOR sum of nimSum and p.
In the end, if nimSum is non-zero, the first player wins. Otherwise, the second player wins.
Implementation
 */
class Solution {
public:
    bool nimGame(vector<int>& piles) {
        int ans = 0;
        for (auto& x : piles)
            ans ^= x;
        return ans;
    }
};
