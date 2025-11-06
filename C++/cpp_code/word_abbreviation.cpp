/*
527. Word Abbreviation

Given an array of n distinct non-empty strings,
you need to generate minimal possible abbreviations for every word following rules below.

1. Begin with the first character and then the number of characters abbreviated, which followed by the last character.
2. If there are any conflict,
that is more than one words share the same abbreviation,
a longer prefix is used instead of only the first character until making the map from word to abbreviation become
unique. In other words, a final abbreviation cannot map to more than one original words.
3. If the abbreviation doesn't make the word shorter, then keep it as original.

Example:
Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]

Note:
Both n and the length of each word will not exceed 400.
The length of each word is greater than 1.
The words consist of lowercase English letters only.
The return answers should be in the same order as the original array.
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
using namespace std;
/*
For example, let's say we have "aabaaa", "aacaaa", "aacdaa", then we start with "a4a", "a4a", "a4a".
Since these are duplicated, we lengthen them to "aa3a", "aa3a", "aa3a". They are still duplicated,
so we lengthen them to "aab2a", "aac2a", "aac2a".
The last two are still duplicated, so we lengthen them to "aacaaa", "aacdaa".

Throughout this process, we were tracking an index prefix[i]
which told us up to what index to take the prefix to.
For example, prefix[i] = 2 means to take a prefix of word[0], word[1], word[2].
*/
class Solution {
private:
    string abbreviate(string s, int k) {
        // k is the length of prefix of the abbreviation, before number
        int length = s.size();
        if (k >= length - 2) {
            // k + 2 will be the length after abbreviation
            return s;
        }

        string result = "";
        result += s.substr(0, k) + to_string(length - 1 - k);
        result.push_back(s.back());
        return result;
    }

public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        vector<string> result;
        vector<int> prefix(n, 1);
        for (string& word : dict) {
            result.push_back(abbreviate(word, 1));
        }

        for (int i = 0; i < n; ++i) {
            while (true) {
                vector<int> mem;
                for (int j = i + 1; j < n; ++j) {
                    if (result[j] == result[i]) {
                        mem.push_back(j);
                    }
                }
                if (mem.empty()) {
                    break;
                }

                mem.push_back(i);
                for (int k : mem) {
                    prefix[k] += 1;
                    result[k] = abbreviate(dict[k], prefix[k]);
                }
            }
        }
        return result;
    }
};