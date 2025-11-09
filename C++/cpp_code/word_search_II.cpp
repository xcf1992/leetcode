/*
212. Word Search II
https://leetcode.com/problems/word-search-ii/

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell,
where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.

Example:
Input:
words = ["oath","pea","eat","rain"] and board =
[
['o','a','a','n'],
['e','t','a','e'],
['i','h','k','r'],
['i','f','l','v']
]
Output: ["eat","oath"]

Note:
You may assume that all inputs are consist of lowercase letters a-z.
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

struct TrieNode {
    bool isWord;
    string word;
    vector<TrieNode*> next;

    TrieNode() {
        word = "";
        isWord = false;
        next.resize(26, nullptr);
    }
};

class Solution {
private:
    TrieNode* root = new TrieNode();
    vector<int> diff = {0, 1, 0, -1, 0};
    int m = 0;
    int n = 0;

    void addWord(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->next[c - 'a'] == nullptr) {
                cur->next[c - 'a'] = new TrieNode();
            }
            cur = cur->next[c - 'a'];
        }
        cur->word = word;
        cur->isWord = true;
    }

    void findWord(vector<string>& result, vector<vector<bool>>& visited, vector<vector<char>>& board, TrieNode* cur,
                  int r, int c) {
        if (r < 0 or c < 0 or r >= m or c >= n or visited[r][c]) {
            return;
        }

        TrieNode* next = cur->next[board[r][c] - 'a'];
        if (next == nullptr) {
            return;
        }

        if (next->isWord) {
            result.push_back(next->word);
            next->isWord = false;  // so we do not put duplicate words into final result
        }

        visited[r][c] = true;
        for (int k = 1; k < diff.size(); ++k) {
            findWord(result, visited, board, next, r + diff[k], c + diff[k - 1]);
        }
        visited[r][c] = false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();

        for (string word : words) {
            addWord(word);
        }

        vector<string> result;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                findWord(result, visited, board, root, i, j);
            }
        }
        return result;
    }
};