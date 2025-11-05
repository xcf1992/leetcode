/*
648. Replace Words
In English, we have a concept called root,
which can be followed by some other words to form another longer word -
let's call this word successor.
For example, the root an, followed by other, which can form another word another.

Now, given a dictionary consisting of many roots and a sentence.
You need to replace all the successor in the sentence with the root forming it.
If a successor has many roots can form it, replace it with the root with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"

Note:

The input will only have lower-case letters.
1 <= dict words number <= 1000
1 <= sentence words number <= 1000
1 <= root length <= 100
1 <= sentence words length <= 1000
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
    bool isRoot;
    vector<TrieNode *> children = vector<TrieNode *>(26, nullptr);

    TrieNode(bool r = false) : isRoot(r) {
    }
};

class Trie {
private:
    TrieNode *root = nullptr;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode *cur = root;
        for (char c: word) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }
        cur->isRoot = true;
    }

    string getRoot(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); ++i) {
            int index = word[i] - 'a';
            if (cur->children[index] == nullptr) {
                return word;
            }

            cur = cur->children[index];
            if (cur->isRoot) {
                return word.substr(0, i + 1);
            }
        }
        return word;
    }
};

class Solution {
private:
    vector<string> splitSentence(string sentence) {
        vector<string> result;
        int cur = 0;
        int pos = sentence.find(' ', cur);
        while (pos != string::npos) {
            string word = sentence.substr(cur, pos - cur);
            result.push_back(word);
            cur = pos + 1;
            pos = sentence.find(' ', cur);
        }
        result.push_back(sentence.substr(cur));
        return result;
    }

public:
    string replaceWords(vector<string> &dict, string sentence) {
        Trie trie;
        for (string word: dict) {
            trie.insert(word);
        }

        vector<string> words = splitSentence(sentence);
        string result = "";
        for (int i = 0; i < words.size(); ++i) {
            result += trie.getRoot(words[i]);
            if (i != words.size() - 1) {
                result += " ";
            }
        }
        return result.substr();
    }
};