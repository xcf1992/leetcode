/*
1451. Rearrange Words in a Sentence
https://leetcode.com/problems/rearrange-words-in-a-sentence/

Given a sentence text
(A sentence is a string of space-separated words) in the following format:

First letter is in upper case.
Each word in text are separated by a single space.
Your task is to rearrange the words in text
such that all words are rearranged in an increasing order of their lengths.
If two words have the same length, arrange them in their original order.

Return the new text following the format shown above.

Example 1:
Input: text = "Leetcode is cool"
Output: "Is cool leetcode"
Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
Output is ordered by length and the new first word starts with capital letter.

Example 2:
Input: text = "Keep calm and code on"
Output: "On and keep calm code"
Explanation: Output is ordered as follows:
"On" 2 letters.
"and" 3 letters.
"keep" 4 letters in case of tie order by position in original text.
"calm" 4 letters.
"code" 4 letters.

Example 3:
Input: text = "To be or not to be"
Output: "To be or to be not"

Constraints:
text begins with a capital letter and then contains lowercase letters and single space between words.
1 <= text.length <= 10^5
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    string arrangeWords(string text) {
        text[0] = tolower(text[0]);
        text.push_back(' ');
        vector<pair<string, int>> words;
        int index = 0;
        string word = "";
        for (int i = 0; i < text.size(); ++i) {
            if (text[i] != ' ') {
                word.push_back(text[i]);
                continue;
            }

            words.push_back({word, index});
            word = "";
            index += 1;
        }

        sort(words.begin(), words.end(), [](pair<string, int>& a, pair<string, int>b) {
            return a.first.size() < b.first.size() or (a.first.size() == b.first.size() and a.second < b.second);
        });

        string result = "";
        for (auto w : words) {
            result += w.first;
            result.push_back(' ');
        }
        result.pop_back();
        result[0] = toupper(result[0]);
        return result;
    }
};
