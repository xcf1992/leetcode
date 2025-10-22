/*
3330. Find the Original Typed String I
https://leetcode.com/problems/find-the-original-typed-string-i/description/

Alice is attempting to type a specific string on her computer.
However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.
You are given a string word, which represents the final output displayed on Alice's screen.
Return the total number of possible original strings that Alice might have intended to type.

Example 1:
Input: word = "abbcccc"
Output: 5
Explanation:
The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".

Example 2:
Input: word = "abcd"
Output: 1
Explanation:
The only possible string is "abcd".

Example 3:
Input: word = "aaaa"
Output: 4

Constraints:
1 <= word.length <= 100
word consists only of lowercase English letters.
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
    int possibleStringCount(string word) {
        int result = 1;
        size_t cur = 0;
        while (cur < word.size()) {
            size_t end = cur + 1;
            while (end < word.size() && word[cur] == word[end]) {
                end += 1;
            }

            result += end - cur - 1;
            cur = end;
        }
        return result;
    }
};
