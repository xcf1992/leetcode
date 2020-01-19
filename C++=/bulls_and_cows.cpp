/*
299. Bulls and Cows
https://leetcode.com/problems/bulls-and-cows/

You are playing the following Bulls and Cows game with your friend:
You write down a number and ask your friend to guess what the number is.
Each time your friend makes a guess,
you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position
(called "bulls")
and how many digits match the secret number but locate in the wrong position (called "cows").
Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess,
use A to indicate the bulls and B to indicate the cows.

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:
Input: secret = "1807", guess = "7810"
Output: "1A3B"
Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.

Example 2:
Input: secret = "1123", guess = "0111"
Output: "1A1B"
Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.

Note:
You may assume that the secret number and your friend's guess only contain digits,
and their lengths are always equal.
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
public:
    string getHint(string secret, string guess) {
        vector<int> count(10, 0);
        int bulls = 0;
        for (int i = 0; i < secret.size(); i++) {
            count[secret[i] - '0'] += 1;
            if (secret[i] == guess[i]) {
                bulls += 1;
            }
        }

        int cows = 0;
        for (int i = 0; i < guess.size(); i++) if (count[guess[i] - '0']) {
            cows += 1;
            count[guess[i] - '0'] -= 1;
        }
        // we return cows - bulls as to remove the number we count bulls as cows
        return to_string(bulls) + "A" + to_string(cows - bulls) + "B";
    }
};
