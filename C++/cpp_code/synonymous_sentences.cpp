/*
1258. Synonymous Sentences
https://leetcode.com/problems/synonymous-sentences/

Given a list of pairs of equivalent words synonyms and a sentence text,
Return all possible synonymous sentences sorted lexicographically.

Example 1:
Input:
synonyms = [["happy","joy"],["sad","sorrow"],["joy","cheerful"]],
text = "I am happy today but was sad yesterday"
Output:
["I am cheerful today but was sad yesterday",
​​​​​​​"I am cheerful today but was sorrow yesterday",
"I am happy today but was sad yesterday",
"I am happy today but was sorrow yesterday",
"I am joy today but was sad yesterday",
"I am joy today but was sorrow yesterday"]

Constraints:
0 <= synonyms.length <= 10
synonyms[i].length == 2
synonyms[0] != synonyms[1]
All words consist of at most 10 English letters only.
text is a single space separated sentence of at most 10 words.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void find(string &word, unordered_set<string> &synonyms, unordered_map<string, vector<string> > &adj) {
        for (string &next: adj[word]) {
            if (synonyms.find(next) == synonyms.end()) {
                synonyms.insert(next);
                find(next, synonyms, adj);
            }
        }
    }

    void dfs(unordered_map<string, vector<string> > &adj, vector<string> &result, string curText, vector<string> &words,
             int start) {
        if (start >= words.size()) {
            result.push_back(curText.substr(1));
            return;
        }

        string &word = words[start];
        if (adj.find(word) == adj.end()) {
            dfs(adj, result, curText + " " + word, words, start + 1);
            return;
        }

        unordered_set<string> synonyms;
        synonyms.insert(word);
        find(word, synonyms, adj);
        for (string replace: synonyms) {
            dfs(adj, result, curText + " " + replace, words, start + 1);
        }
    }

public:
    vector<string> generateSentences(vector<vector<string> > &synonyms, string text) {
        unordered_map<string, vector<string> > adj;
        for (auto &word: synonyms) {
            adj[word[0]].push_back(word[1]);
            adj[word[1]].push_back(word[0]);
        }

        stringstream ss(text);
        vector<string> words;
        string buf;
        while (ss >> buf) {
            words.push_back(buf);
        }

        vector<string> result;
        dfs(adj, result, "", words, 0);
        sort(result.begin(), result.end());
        return result;
    }
};