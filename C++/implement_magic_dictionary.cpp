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

class TrieNode {
private:
    bool isRoot;
    vector<TrieNode*> nodes = vector<TrieNode*>(26, nullptr);

public:
    void insert(string word, int start) {
        if (start == word.size()) {
            isRoot = true;
            return;
        }

        if (nodes[word[start] - 'a'] == nullptr) {
            nodes[word[start] - 'a'] = new TrieNode();
        }

        nodes[word[start] - 'a'] -> insert(word, start + 1);
    }

    bool find(string word, int start, int modification) {
        if (start == word.size()) {
            return isRoot && modification == 1;
        }

        if (modification > 1) {
            return false;
        }

        for (int i = 0; i < 26; i++) {
            TrieNode* node = nodes[i];
            if (node && node -> find(word, start + 1, modification + (i == word[start] - 'a' ? 0 : 1))) {
                return true;
            }
        }
        return false;
    }
};

class MagicDictionary {
private:
    Trie* root;
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        root = new Trie;
    }

    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (string word : dict) {
            root -> insert(word, 0);
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return root -> find(word, 0, 0);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */