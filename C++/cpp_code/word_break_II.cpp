/*
140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

Example 2:
Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
    // dfs with memo
private:
    unordered_map<string, vector<string>> memo;

    vector<string> generate(unordered_set<string>& dict, string s) {
        if (s == "") {
            return {""};
        }
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }

        for (int i = s.size() - 1; i >= 0; --i) {
            string word = s.substr(i);
            if (dict.find(word) == dict.end()) {
                continue;
            }

            vector<string> breakWords = generate(dict, s.substr(0, i));
            for (string& bw : breakWords) {
                memo[s].push_back(bw + (bw == "" ? "" : " ") + word);
            }
        }
        return memo[s];
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return generate(dict, s);
    }
};

class Solution1 {
    // dp Memory limit exceed
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        vector<vector<string>> dp(n + 1);
        dp[0].push_back("");
        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (dp[j].size() == 0) {
                    continue;
                }
                string word = s.substr(j, i - j);
                if (dict.find(word) != dict.end()) {
                    for (string& bw : dp[j]) {
                        dp[i].push_back(bw + (bw == "" ? "" : " ") + word);
                    }
                }
            }
        }
        return dp[n];
    }
};