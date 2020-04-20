/*
1419. Minimum Number of Frogs Croaking
https://leetcode.com/problems/minimum-number-of-frogs-croaking/

Given the string croakOfFrogs,
which represents a combination of the string "croak" from different frogs,
that is, multiple frogs can croak at the same time,
so multiple “croak” are mixed.
Return the minimum number of different frogs to finish all the croak in the given string.

A valid "croak" means a frog is printing 5 letters
‘c’, ’r’, ’o’, ’a’, ’k’ sequentially.
The frogs have to print all five letters to finish a croak.
If the given string is not a combination of valid "croak" return -1.

Example 1:
Input: croakOfFrogs = "croakcroak"
Output: 1
Explanation: One frog yelling "croak" twice.

Example 2:
Input: croakOfFrogs = "crcoakroak"
Output: 2
Explanation: The minimum number of frogs is two.
The first frog could yell "crcoakroak".
The second frog could yell later "crcoakroak".

Example 3:
Input: croakOfFrogs = "croakcrook"
Output: -1
Explanation: The given string is an invalid combination of "croak" from different frogs.

Example 4:
Input: croakOfFrogs = "croakcroa"
Output: -1

Constraints:
1 <= croakOfFrogs.length <= 10^5
All characters in the string are: 'c', 'r', 'o', 'a' or 'k'.
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
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        int cnt[5] = {}, frogs = 0, max_frogs = 0;
        for (auto ch : croakOfFrogs) {
            auto n = string("croak").find(ch);
            ++cnt[n];
            if (n == 0)
                max_frogs = max(max_frogs, ++frogs);
            else if (--cnt[n - 1] < 0)
                return -1;
            else if (n == 4)
                --frogs;
        }
        return frogs == 0 ? max_frogs : -1;
    }
};
