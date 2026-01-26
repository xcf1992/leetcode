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
#include <climits>
#include <map>
#include <set>
using namespace std;

struct TrieNode {
    bool is_word_;
    string word_;
    vector<TrieNode*> children_;

    TrieNode() {
        word_ = "";
        is_word_ = false;
        children_.resize(26, nullptr);
    }
};

class Solution {
private:
    TrieNode* root_ = new TrieNode();
    vector<int> diff_ = {0, 1, 0, -1, 0};
    int m = 0;
    int n = 0;

    void add_word(string word) {
        TrieNode* cur = root_;
        for (char c : word) {
            if (cur->children_[c - 'a'] == nullptr) {
                cur->children_[c - 'a'] = new TrieNode();
            }
            cur = cur->children_[c - 'a'];
        }
        cur->word_ = word;
        cur->is_word_ = true;
    }

    void findWord(vector<string>& result, vector<vector<bool>>& visited, vector<vector<char>>& board, TrieNode* cur,
                  int r, int c) {
        if (r < 0 or c < 0 or r >= m or c >= n or visited[r][c]) {
            return;
        }

        TrieNode* next = cur->children_[board[r][c] - 'a'];
        if (next == nullptr) {
            return;
        }

        if (next->is_word_) {
            result.push_back(next->word_);
            next->is_word_ = false;  // so we do not put duplicate words into final result
        }

        visited[r][c] = true;
        for (int k = 1; k < diff_.size(); ++k) {
            findWord(result, visited, board, next, r + diff_[k], c + diff_[k - 1]);
        }
        visited[r][c] = false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();

        for (string word : words) {
            add_word(word);
        }

        vector<string> result;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                findWord(result, visited, board, root_, i, j);
            }
        }
        return result;
    }
};