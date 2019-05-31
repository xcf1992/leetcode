/*
 527. Word Abbreviation

 Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.

 Begin with the first character and then the number of characters abbreviated, which followed by the last character.
 If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique. In other words, a final abbreviation cannot map to more than one original words.
 If the abbreviation doesn't make the word shorter, then keep it as original.
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

class Solution {
private:
    void generate(vector<string>& result, int start, int preNum, string abbreviation, string& word) {
        if (start >= word.size()) {
            if (preNum != 0) {
                abbreviation += to_string(preNum);
            }
            result.push_back(abbreviation);
            return;
        }

        generate(result, start + 1, preNum + 1, abbreviation, word);
        if (preNum != 0) {
            abbreviation += to_string(preNum);
        }
        abbreviation.push_back(word[start]);
        generate(result, start + 1, 0, abbreviation, word);
    }
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        generate(result, 0, 0, "", word);
        return result;
    }
};

class Solution1 {
private:
    string abbreviate(string s, int k) {
        int length = s.size();
        if (k >= length - 2) {
            return s;
        }

        string result = "";
        result += s.substr(0, k);
        result += to_string(length - 1 - k);
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
