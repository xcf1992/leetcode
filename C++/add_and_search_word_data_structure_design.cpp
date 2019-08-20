/*
211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A
. means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

struct TrieNode {
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    bool isWord = false;
    TrieNode(bool word = false): isWord(word) {}
};

class Trie {
private:
    TrieNode* root;

    bool searchWord(TrieNode* cur, string s) {
        for (int i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            if (isalpha(s[i])) {
                if (cur -> children[ch] == nullptr) {
                    return false;
                }
                else {
                    cur = cur -> children[ch];
                }
            }
            else {
                for (int j = 0; j < 26; j++) {
                    if (cur -> children[j] != nullptr && searchWord(cur -> children[j], s.substr(i + 1))) {
                        return true;
                    }
                }
                return false;
            }
        }
        return cur -> isWord;
    }
public:
    Trie(): root(new TrieNode()) {}

    void add(string s) {
        TrieNode* cur = root;
        for (int i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            if (cur -> children[ch] == nullptr) {
                cur -> children[ch] = new TrieNode();
            }
            cur = cur -> children[ch];
        }
        cur -> isWord = true;
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
    WordDictionary() {}

    /** Adds a word into the data structure. */
    void addWord(string word) {
        trie.add(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return trie.search(word);
    }
};
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
