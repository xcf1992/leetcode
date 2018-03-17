/*
 Given a set of words (without duplicates), find all word squares you can build from them.
 
 A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).
 
 For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.
 
 b a l l
 a r e a
 l e a d
 l a d y
 Note:
 There are at least 1 and at most 1000 words.
 All words will have the exact same length.
 Word length is at least 1 and at most 5.
 Each word contains only lowercase English alphabet a-z.
 Example 1:
 
 Input:
 ["area","lead","wall","lady","ball"]
 
 Output:
 [
     [ "wall",
       "area",
       "lead",
       "lady"
     ],
     [ "ball",
       "area",
       "lead",
       "lady"
     ]
 ]
 
 Explanation:
 The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 Example 2:
 
 Input:
 ["abat","baba","atan","atal"]
 
 Output:
 [
     [ "baba",
       "abat",
       "baba",
       "atan"
     ],
     [ "baba",
       "abat",
       "baba",
       "atal"
     ]
 ]
 
 Explanation:
 The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
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
#include <set>
using namespace std;

struct TrieNode {
    vector<int> index;
    vector<TrieNode*> children;
    
    TrieNode() {
        children.resize(26, nullptr);
    }
};

class Solution {
private:
    TrieNode* construct(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (int i = 0; i < words.size(); i++) {
            string& word = words[i];
            TrieNode* cur = root;
            for (int j = 0; j < word.size(); j++) {
                if (cur -> children[word[j] - 'a'] == nullptr) {
                    cur -> children[word[j] - 'a'] = new TrieNode();
                }
                cur = cur -> children[word[j] - 'a'];
                cur -> index.push_back(i);
            }
        }
        return root;
    }
    
    void dfs(vector<vector<string>>& result, vector<string>& square, vector<string>& words, TrieNode* root, int row) {
        if (row == square.size()) {
            result.push_back(square);
            return;
        }
        
        TrieNode* cur = root;
        for (int i = 0; i < row; i++) {
            if (cur -> children[square[i][row] - 'a'] == nullptr) {
                return;
            }
            cur = cur -> children[square[i][row] - 'a'];
        }
        
        for (int i : cur -> index) {
            square[row] = words[i];
            dfs(result, square, words, root, row + 1);
        }
    }
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n = words.size();
        vector<vector<string>> result;
        if (n == 0) {
            return result;
        }
        int length = words[0].size();
        vector<string> square(length, "");
        TrieNode* root = construct(words);
        for (string& word : words) {
            square[0] = word;
            dfs(result, square, words, root, 1);
        }
        return result;
    }
};
