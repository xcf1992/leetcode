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

/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.
*/
class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> letter;
        for (char c : s) {
            letter[c] += 1;
        }

        int odd = 0;
        for (auto it = letter.begin(); it != letter.end(); it++) {
            if (it -> second % 2 == 1) {
                odd += 1;
            }
        }

        return odd <= 1;
    }
};