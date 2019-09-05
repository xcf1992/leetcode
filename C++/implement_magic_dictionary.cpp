/*
676. Implement Magic Dictionary
Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word,
and judge whether if you modify exactly one character into another character in this word,
the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False

Note:
1. You may assume that all the inputs are consist of lowercase letters a-z.
2. For contest purpose, the test data is rather small by now.
   You could think about highly efficient algorithm after the contest.
3. Please remember to RESET your class variables declared in class MagicDictionary,
   as static/class variables are persisted across multiple test cases.
   Please see here for more details.
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

class MagicDictionary {
private:
    unordered_set<string> magician;
public:
    /** Initialize your data structure here.*/
    MagicDictionary() {}

    /** Build a dictionary through a list of words*/
    void buildDict(vector<string> dict) {
        for (string word : dict) {
            magician.insert(word);
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character*/
    bool search(string word) {
        for (int i = 0; i < word.size(); ++i) {
            char c = word[i];
            for (int j = 0; j < 26; j++) {
                if ('a' + j == c) {
                    continue;
                }

                word[i] = 'a' + j;
                if (magician.find(word) != magician.end()) {
                    return true;
                }
            }
            word[i] = c;
        }
        return false;
    }
};

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
            return isRoot and modification == 1;
        }

        if (modification > 1) {
            return false;
        }

        for (int i = 0; i < 26; i++) {
            TrieNode* node = nodes[i];
            if (node and node -> find(word, start + 1, modification + (i == word[start] - 'a' ? 0 : 1))) {
                return true;
            }
        }
        return false;
    }
};

class MagicDictionary1 {
private:
    TrieNode* root;
public:
    /** Initialize your data structure here.*/
    MagicDictionary() {
        root = new TrieNode();
    }

    /** Build a dictionary through a list of words*/
    void buildDict(vector<string> dict) {
        for (string word : dict) {
            root -> insert(word, 0);
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character*/
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