/*
294. Flip Game II
https://leetcode.com/problems/flip-game-ii/

You are playing the following Flip Game with your friend:
Given a string that contains only these two characters: + and -,
you and your friend take turns to flip two consecutive "++" into "--".
The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

Example:
Input: s = "++++"
Output: true
Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.
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
using namespace std;

class Solution {
private:
    unordered_map<string, bool> firstWin;
public:
    bool canWin(string s) {
        if (firstWin.find(s) != firstWin.end()) {
            return firstWin[s];
        }

        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '+' and s[i - 1] == '+') {
                s[i] = s[i - 1] = '-';
                if (firstWin.find(s) == firstWin.end()) {
                    firstWin[s] = canWin(s);
                }

                if (!firstWin[s]) {
                    return true;
                }
                s[i] = s[i - 1] = '+';
            }
        }
        firstWin[s] = false;
        return false;
    }
};

class Solution1 {
private:
    bool canFlip(string s) {
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '+' and s[i - 1] == '+') {
                return true;
            }
        }
        return false;
    }
public:
    bool canWin(string s) {
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '+' and s[i - 1] == '+') {
                s[i] = s[i - 1] = '-';
                if (!canFlip(s)) {
                    return true;
                }
                if (!canWin(s)) {
                    return true;
                }
                s[i] = s[i - 1] = '+';
            }
        }
        return false;
    }
};
