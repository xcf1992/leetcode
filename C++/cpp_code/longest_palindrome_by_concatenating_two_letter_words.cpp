/*
https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/description/
2131. Longest Palindrome by Concatenating Two Letter Words

You are given an array of strings words. Each element of words consists of two lowercase English letters.

Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each
element can be selected at most once.

Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.

A palindrome is a string that reads the same forward and backward.



Example 1:

Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.
Example 2:

Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.
Example 3:

Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".


Constraints:

1 <= words.length <= 105
words[i].length == 2
words[i] consists of lowercase English letters.
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
#include <map>
using namespace std;

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> word_cnt;
        for (string w : words) {
            word_cnt[w] += 1;
        }

        int count = 0;
        int already_palindrome = 0;
        for (const auto& [word, cnt] : word_cnt) {
            string reverse_word = word;
            reverse(reverse_word.begin(), reverse_word.end());

            if (word == reverse_word) {
                count += (cnt / 2) * 4;
                if (cnt % 2 != 0) {
                    already_palindrome = 1;
                }
            } else if (word < reverse_word && word_cnt.count(reverse_word)) {
                count += min(cnt, word_cnt[reverse_word]) * 4;
            }
        }
        return count + already_palindrome * 2;
    }
};