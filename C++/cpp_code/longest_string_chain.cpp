/*
1048. Longest String Chain

Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2
if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.
For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1,
where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.

Example 1:
Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".

Note:
1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of English lowercase letters.
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
using namespace std;

class Solution {
    // bottom up
public:
    int longestStrChain(vector<string> &words) {
        sort(words.begin(), words.end(), [](string &a, string &b) {
            return a.size() < b.size();
        });

        unordered_map<string, int> dp;
        int result = 1;
        for (string &word: words) {
            dp[word] = 1;
            for (int i = 0; i < word.size(); ++i) {
                string pre = word.substr(0, i) + word.substr(i + 1);
                if (dp.find(pre) != dp.end()) {
                    dp[word] = max(dp[word], 1 + dp[pre]);
                }
            }
            result = max(result, dp[word]);
        }
        return result;
    }
};

class Solution1 {
    // top down
private:
    int find(unordered_map<string, int> &dp, unordered_set<string> &words, string word) {
        if (dp.find(word) != dp.end()) {
            return dp[word];
        }

        dp[word] = 1;
        for (int i = 0; i < word.size(); ++i) {
            string temp = word.substr(0, i) + word.substr(i + 1);
            if (words.find(temp) != words.end()) {
                dp[word] = max(dp[word], find(dp, words, temp) + 1);
            }
        }
        return dp[word];
    }

public:
    int longestStrChain(vector<string> &words) {
        sort(words.begin(), words.end());
        unordered_set<string> dict;
        for (string &word: words) {
            dict.insert(word);
        }

        int n = words.size();
        unordered_map<string, int> dp;
        int result = 1;
        for (int i = n - 1; i >= 0; --i) {
            result = max(result, find(dp, dict, words[i]));
        }
        return result;
    }
};