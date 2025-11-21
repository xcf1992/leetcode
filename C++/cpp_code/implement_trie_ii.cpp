/*
https://leetcode.com/problems/implement-trie-ii-prefix-tree/description/
1804. Implement Trie II (Prefix Tree)

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a
dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
int countWordsEqualTo(String word) Returns the number of instances of the string word in the trie.
int countWordsStartingWith(String prefix) Returns the number of strings in the trie that have the string prefix as a
prefix. void erase(String word) Erases the string word from the trie.


Example 1:

Input
["Trie", "insert", "insert", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsEqualTo",
"countWordsStartingWith", "erase", "countWordsStartingWith"]
[[], ["apple"], ["apple"], ["apple"], ["app"], ["apple"], ["apple"], ["app"], ["apple"], ["app"]]
Output
[null, null, null, 2, 2, null, 1, 1, null, 0]

Explanation
Trie trie = new Trie();
trie.insert("apple");               // Inserts "apple".
trie.insert("apple");               // Inserts another "apple".
trie.countWordsEqualTo("apple");    // There are two instances of "apple" so return 2.
trie.countWordsStartingWith("app"); // "app" is a prefix of "apple" so return 2.
trie.erase("apple");                // Erases one "apple".
trie.countWordsEqualTo("apple");    // Now there is only one instance of "apple" so return 1.
trie.countWordsStartingWith("app"); // return 1
trie.erase("apple");                // Erases "apple". Now the trie is empty.
trie.countWordsStartingWith("app"); // return 0


Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, countWordsEqualTo, countWordsStartingWith, and erase.
It is guaranteed that for any function call to erase, the string word will exist in the trie.
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
    vector<TrieNode*> next_;
    int word_cnt_;
    int prefix_cnt_;

    TrieNode() {
        next_.resize(26, nullptr);
        word_cnt_ = 0;
        prefix_cnt_ = 0;
    }
};

class Trie {
private:
    TrieNode* root_;

public:
    Trie() {
        root_ = new TrieNode();
    }

    void insert(string word) {
        TrieNode* cur = root_;
        for (int i = 0; i < word.size(); i++) {
            int pos = word[i] - 'a';
            if (cur->next_[pos] == nullptr) {
                cur->next_[pos] = new TrieNode();
            }
            cur->next_[pos]->prefix_cnt_ += 1;
            cur = cur->next_[pos];
        }
        cur->word_cnt_ += 1;
    }

    int countWordsEqualTo(string word) {
        TrieNode* cur = root_;
        for (int i = 0; i < word.size(); i++) {
            int pos = word[i] - 'a';
            if (cur->next_[pos] == nullptr) {
                return 0;
            }
            cur = cur->next_[pos];
        }
        return cur->word_cnt_;
    }

    int countWordsStartingWith(string prefix) {
        TrieNode* cur = root_;
        for (int i = 0; i < prefix.size(); i++) {
            int pos = prefix[i] - 'a';
            if (cur->next_[pos] == nullptr) {
                return 0;
            }
            cur = cur->next_[pos];
        }
        return cur->prefix_cnt_;
    }

    void erase(string word) {
        TrieNode* cur = root_;
        for (int i = 0; i < word.size(); i++) {
            int pos = word[i] - 'a';
            if (cur->next_[pos] == nullptr) {
                // error state
                return;
            }
            cur->next_[pos]->prefix_cnt_ -= 1;
            cur = cur->next_[pos];
        }
        cur->word_cnt_ -= 1;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */