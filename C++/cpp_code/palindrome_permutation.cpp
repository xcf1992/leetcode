/*
266. Palindrome Permutation
Given a string, determine if a permutation of the string could form a palindrome.

Example 1:

Input: "code"
Output: false
Example 2:

Input: "aab"
Output: true
Example 3:

Input: "carerac"
Output: true
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
using namespace std;

class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> letter;
        for (char c : s) {
            letter[c] += 1;
        }

        int odd = 0;
        for (auto& it : letter)
            if (it.second % 2 == 1) {
                odd += 1;
            }
        return odd <= 1;
    }
};