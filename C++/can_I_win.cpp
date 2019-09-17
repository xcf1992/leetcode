/*
464. Can I Win
https://leetcode.com/problems/can-i-win/

In the "100 game," two players take turns adding,
to a running total, any integer from 1..10.
The player who first causes the running total to reach or exceed 100 wins.

What if we change the game so that players cannot re-use integers?

For example,
two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.

Given an integer maxChoosableInteger and another integer desiredTotal,
determine if the first player to move can force a win,
assuming both players play optimally.

You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.

Example
Input:
maxChoosableInteger = 10
desiredTotal = 11
Output:
false
Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
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
    bool canWin(int total, int usedNumMask, vector<unordered_map<int, bool>>& cache, int maxNum) {
        if (total <= 0) {
            return false;
        }

        if (cache[total].find(usedNumMask) != cache[total].end()) {
            return cache[total][usedNumMask];
        }

        for (int i = 0; i < maxNum; i++) {
            if (((1 << i) & usedNumMask) == 0) {
                if (!canWin(total - i - 1, usedNumMask | (1 << i), cache, maxNum)) {
                    cache[total][usedNumMask] = true;
                    return true;
                }
            }
        }
        cache[total][usedNumMask] = false;
        return false;
    }
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (maxChoosableInteger >= desiredTotal) {
            return true;
        }
        if (maxChoosableInteger * (maxChoosableInteger + 1) < desiredTotal * 2) {
            return false;
        }

        vector<unordered_map<int, bool>> cache(desiredTotal + 1);
        return canWin(desiredTotal, 0, cache, maxChoosableInteger);
    }
};
