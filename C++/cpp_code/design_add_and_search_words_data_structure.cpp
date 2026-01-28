/*
https://leetcode.com/problems/design-add-and-search-words-data-structure/description
211. Design Add and Search Words Data Structure

Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word
may contain dots '.' where dots can be matched with any letter.


Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True


Constraints:

1 <= word.length <= 25
word in addWord consists of lowercase English letters.
word in search consist of '.' or lowercase English letters.
There will be at most 2 dots in word for search queries.
At most 104 calls will be made to addWord and search.
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

struct TrieNode {
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    bool isWord = false;
    TrieNode(bool word = false) : isWord(word) {
    }
};

class Trie {
private:
    TrieNode* root;

    bool searchWord(TrieNode* cur, string s) {
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i])) {
                int ch = s[i] - 'a';
                if (cur->children[ch] == nullptr) {
                    return false;
                }
                cur = cur->children[ch];
            } else {
                for (int j = 0; j < 26; j++) {
                    if (cur->children[j] != nullptr && searchWord(cur->children[j], s.substr(i + 1))) {
                        return true;
                    }
                }
                return false;
            }
        }
        return cur->isWord;
    }

public:
    Trie() : root(new TrieNode()) {
    }

    void add(string s) {
        TrieNode* cur = root;
        for (int i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            if (cur->children[ch] == nullptr) {
                cur->children[ch] = new TrieNode();
            }
            cur = cur->children[ch];
        }
        cur->isWord = true;
    }

    bool search(string s) {
        return searchWord(root, s);
    }
};

class WordDictionary {
private:
    Trie trie;

public:
    /** Initialize your data structure here. */
    WordDictionary() {
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        trie.add(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one
     * letter. */
    bool search(string word) {
        return trie.search(word);
    }
};