/*
126. Word Ladder II
Given two words (beginWord and endWord),
and a dictionary's word list,
find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> visited;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<vector<string>> bfs;

        int len = 1;
        int minLen = INT_MAX;
        bfs.push({beginWord});
        while (!bfs.empty()) {
            vector<string> ladder = bfs.front();
            bfs.pop();

            //"visited" records all the visited nodes on this level
            //these words will never be visited again after this level
            //and should be removed from wordList. This is guaranteed
            // by the shortest path.
            if (ladder.size() > len) { //reach a new level
                for (string word : visited) {
                    dict.erase(word);
                }
                visited.clear();
                if (ladder.size() > minLen) {
                    break;
                }
                else {
                    len = ladder.size();
                }
            }

            string curWord = ladder.back();
            for (int i = 0; i < curWord.size(); ++i) {
                string nextWord = curWord;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == curWord[i]) {
                        continue;
                    }
                    nextWord[i] = c;
                    /*
                    * we do not check if visited here for current level, because it may happen different paths come to the same word at this level
                    * for example "red" -> "tax", with ["ted","tex","red","tax","tad","den","rex","pee"]
                    * correct result is [["red","ted","tad","tax"],["red","ted","tex","tax"],["red","rex","tex","tax"]]
                    * the 2nd and 3rd both will have tex at the 3rd place
                    * and that's why we need to cleard the words in the beginning when we enter a new level
                   */
                    if (dict.find(nextWord) != dict.end()) {
                        visited.insert(nextWord);
                        vector<string> newLadder = ladder;
                        newLadder.push_back(nextWord);
                        if (nextWord == endWord) {
                            minLen = len;
                            result.push_back(newLadder);
                        }
                        else {
                            bfs.push(newLadder);
                        }
                    }
                }
            }
        }
        return result;
    }
};

class Solution1 { //TLE
private:
    unordered_map<string, vector<string>> dict;
    void dfs(unordered_set<string>& visited, vector<vector<string>>& result, vector<string>& ladder, int& minLen, string& endWord) {
        string curWord = ladder.back();
        if (curWord == endWord) {
            if (ladder.size() < minLen) {
                result.clear();
                minLen = ladder.size();
                result.push_back(ladder);
                return;
            }
            if (ladder.size() == minLen) {
                result.push_back(ladder);
            }
            return;
        }

        if (ladder.size() >= minLen) {
            return;
        }

        for (int i = 0; i < curWord.size(); ++i) {
            string temp = curWord.substr(0, i) + "*" + curWord.substr(i + 1);
            for (string& nextWord : dict[temp]) {
                if (visited.find(nextWord) == visited.end()) {
                    visited.insert(nextWord);
                    ladder.push_back(nextWord);
                    dfs(visited, result, ladder, minLen, endWord);
                    ladder.pop_back();
                    visited.erase(nextWord);
                }
            }
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        for (string& word : wordList) {
            for (int i = 0; i < word.size(); ++i) {
                string temp = word.substr(0, i) + "*" + word.substr(i + 1);
                dict[temp].push_back(word);
            }
        }

        vector<vector<string>> result;
        vector<string> ladder;
        unordered_set<string> visited;
        ladder.push_back(beginWord);
        visited.insert(beginWord);
        int minLen = INT_MAX;
        dfs(visited, result, ladder, minLen, endWord);
        return result;
    }
};
