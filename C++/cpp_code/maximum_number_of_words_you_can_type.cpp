/*
https://leetcode.com/problems/maximum-number-of-words-you-can-type/description/
1935. Maximum Number of Words You Can Type

There is a malfunctioning keyboard where some letter keys do not work. All other keys on the keyboard work properly.

Given a string text of words separated by a single space (no leading or trailing spaces) and a string brokenLetters of
all distinct letter keys that are broken, return the number of words in text you can fully type using this keyboard.



Example 1:

Input: text = "hello world", brokenLetters = "ad"
Output: 1
Explanation: We cannot type "world" because the 'd' key is broken.
Example 2:

Input: text = "leet code", brokenLetters = "lt"
Output: 1
Explanation: We cannot type "leet" because the 'l' and 't' keys are broken.
Example 3:

Input: text = "leet code", brokenLetters = "e"
Output: 0
Explanation: We cannot type either word because the 'e' key is broken.


Constraints:

1 <= text.length <= 104
0 <= brokenLetters.length <= 26
text consists of words separated by a single space without any leading or trailing spaces.
Each word only consists of lowercase English letters.
brokenLetters consists of distinct lowercase English letters.
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
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> wrong_letters(brokenLetters.begin(), brokenLetters.end());
        int start = 0;
        int n = text.length();
        int rst = 0;
        while (start < n) {
            int end = start;
            bool can_type = true;
            while (end < n && text[end] != ' ') {
                if (wrong_letters.find(text[end]) != wrong_letters.end()) {
                    can_type = false;
                }
                end += 1;
            }

            rst += can_type ? 1 : 0;
            start = end + 1;
        }
        return rst;
    }
};
