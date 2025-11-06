/*
472. Concatenated Words

Given a list of words (without duplicates),
please write a program that returns all concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
"dogcatsdog" can be concatenated by "dog", "cats" and "dog";
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
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
private:
    bool canForm(string word, unordered_set<string>& preWords) {
        if (preWords.empty()) {
            return false;
        }

        int n = word.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] and preWords.find(word.substr(j, i - j)) != preWords.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }

public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort(words.begin(), words.end(), [](string& a, string& b) { return a.size() < b.size(); });

        vector<string> result;
        unordered_set<string> preWords;
        for (string& word : words) {
            if (canForm(word, preWords)) {
                result.push_back(word);
            }
            preWords.insert(word);
        }
        return result;
    }
};