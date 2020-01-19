/*
208. Implement Trie (Prefix Tree)
https://leetcode.com/problems/implement-trie-prefix-tree/

Implement a trie with insert, search, and startsWith methods.

Example:
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");
trie.search("app");     // returns true

Note:
You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.
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
using namespace std;

struct TrieNode {
    vector<TrieNode *> next;
    bool end;

    TrieNode() {
        next.resize(26, nullptr);
        end = false;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
        root -> end = true;
    }

    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode* cur = root;
        for (int i = 0; i < s.size(); i++) {
            int pos = s[i] - 'a';
            if (cur -> next[pos] == nullptr) {
                cur -> next[pos] = new TrieNode();
            }
            cur = cur -> next[pos];
        }
        cur -> end = true;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode* cur = root;
        for (int i = 0; i < key.size(); i++) {
            int pos = key[i] - 'a';
            if (cur -> next[pos] == nullptr) {
                return false;
            }
            cur = cur -> next[pos];
        }
        return cur -> end;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            int pos = prefix[i] - 'a';
            if (cur -> next[pos] == nullptr) {
                return false;
            }
            cur = cur -> next[pos];
        }
        return true;
    }
};
/*
Your Trie object will be instantiated and called as such:
Trie* obj = new Trie();
obj -> insert(word);
bool param_2 = obj -> search(word);
bool param_3 = obj -> startsWith(prefix);
*/