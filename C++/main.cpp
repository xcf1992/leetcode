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
#include <numeric>
using namespace std;

struct TrieNode {
    bool isRoot;
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    TrieNode(bool r = false) : isRoot(r) {}
};

class Trie {
private:
    TrieNode* root = nullptr;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            int index = c - 'a';
            if (cur -> children[index] == nullptr) {
                cur -> children[index] = new TrieNode();
            }
            cur = cur -> children[index];
        }
        cur -> isRoot = true;
    }

    string getRoot(string word) {
        TrieNode* cur = root;
        for (int i = 0; i < word.size(); ++i) {
            int index = word[i] - 'a';
            if (cur -> children[index] == nullptr) {
                return word;
            }

            cur = cur -> children[index];
            if (cur -> isRoot) {
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
    string replaceWords(vector<string> dict, string sentence) {
        Trie trie;
        for (string word : dict) {
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

int main() {
    Solution s;
    vector<int> temp({-4,-2,2,4});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.replaceWords({"cat", "bat", "rat"}, "the cattle was rattled by the battery");
}
