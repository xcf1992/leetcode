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

class Trie {
private:
    bool isRoot;
    Trie* nodes[26] = {};
public:
    void insert(string word, int start) {
        if (start == word.size()) {
            isRoot = true;
            return;
        }

        if (nodes[word[start] - 'a'] == nullptr) {
            nodes[word[start] - 'a'] = new Trie();
            nodes[word[start] - 'a'] -> insert(word, start + 1);
        }
    }

    string root(string word, int start) {
        if (start == word.size() && isRoot) {
            return word.substr(0, start);
        }

        if (nodes[word[start]] - 'a' == nullptr) {
            return word;
        }

        return nodes[word[start] - 'a'] -> root(word, start + 1);
    }
};
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        string result;
        Trie t;
        for (string root : dict) {
            t.insert(root, 0);
        }

        int start = 0;
        while (start < sentence.size()) {
            if (sentence[start] == ' ') {
                result += " ";
                start += 1;
            }
            else {
                int len = 1;
                while (start + len < sentence.size() && sentence[start + len] != ' ') {
                    len += 1;
                }
                string word = sentence.substr(start, len - 1);
                result += t.root(word, 0);
                start += len;
            }
        }
        return result;
    }
};