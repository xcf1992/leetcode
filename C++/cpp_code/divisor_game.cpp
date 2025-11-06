/*
1025. Divisor Game

Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number N on the chalkboard.
On each player's turn, that player makes a move consisting of:

Choosing any x with 0 < x < N and N % x == 0.
Replacing the number N on the chalkboard with N - x.
Also, if a player cannot make a move, they lose the game.

Return True if and only if Alice wins the game, assuming both players play optimally.

Example 1:
Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:
Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

Note:
1 <= N <= 1000
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
using namespace std;

class Solution {
private:
    bool check(int N, vector<int>& firstWin) {
        if (firstWin[N] == 0) {
            return false;
        }

        if (firstWin[0] == 1) {
            return true;
        }

        for (int i = 1; i <= sqrt(N); i++) {
            if (N % i == 0 and !check(N - i, firstWin)) {
                firstWin[N] = 1;
                return true;
            }
        }
        firstWin[N] = 0;
        return false;
    }

public:
    bool divisorGame(int N) {
        vector<int> firstWin(N + 1, -1);
        firstWin[0] = 0;
        firstWin[1] = 0;
        return check(N, firstWin);
    }
};