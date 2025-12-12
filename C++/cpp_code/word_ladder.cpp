/*
https://leetcode.com/problems/word-ladder/
127. Word Ladder

Given two words (beginWord and endWord),
and a dictionary's word list,
find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Example 2:
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
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
#include <numeric>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, vector<string>> dict;
        for (string& word : wordList) {
            for (int i = 0; i < word.size(); ++i) {
                string temp = word.substr(0, i) + "*" + word.substr(i + 1);
                dict[temp].push_back(word);
            }
        }

        unordered_set<string> visited;
        visited.insert(beginWord);
        queue<string> bfs;
        bfs.push(beginWord);
        int step = 1;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; ++i) {
                string cur_word = bfs.front();
                bfs.pop();

                if (cur_word == endWord) {
                    return step;
                }

                for (int j = 0; j < cur_word.size(); ++j) {
                    string temp = cur_word.substr(0, j) + "*" + cur_word.substr(j + 1);
                    for (string& next_word : dict[temp]) {
                        if (visited.find(next_word) != visited.end()) {
                            continue;
                        }
                        bfs.push(next_word);
                        visited.insert(next_word);
                    }
                }
            }
            step += 1;
        }
        return 0;
    }
};