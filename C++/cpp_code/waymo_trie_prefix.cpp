/*
给定一个单词列表（Words List），构造一个数据结构。给定一个前缀（Prefix），返回所有以该前缀开头的单词。
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

struct TrieNode {
    vector<TrieNode*> children;
    bool is_end;

    TrieNode() {
        is_end = false;
        children.clear();
        children.resize(26, nullptr);
    }
};

class Solution {
private:
    TrieNode* root_;

    void insert(string& word) {
        TrieNode* curr = root_;
        for (char c : word) {
            if (curr->children[c - 'a'] == nullptr) {
                curr->children[c - 'a'] = new TrieNode();
            }
            curr = curr->children[c - 'a'];
        }
        curr->is_end = true;
    }

    void collect(TrieNode* curr, string& word, vector<string>& rst) {
        if (curr->is_end) {
            rst.push_back(word);
        }

        for (int i = 0; i < 26; i++) {
            if (curr->children[i] != nullptr) {
                word.push_back('a' + i);
                collect(curr->children[i], word, rst);
                word.pop_back();
            }
        }
    }

public:
    Solution() {
        root_ = new TrieNode();
    }

    void build_trie(vector<string>& words) {
        for (string& word : words) {
            insert(word);
        }
    }

    vector<string> find_by_prefix(string& prefix) {
        vector<string> rst;
        TrieNode* curr = root_;
        for (char c : prefix) {
            if (curr->children[c - 'a'] == nullptr) {
                return rst;
            }
            curr = curr->children[c - 'a'];
        }

        string word = prefix;
        collect(curr, word, rst);
        return rst;
    }
};

// ─── Demo ───
int main() {
    vector<string> words = {"apple",  "app", "application", "apply", "bat", "ball",
                            "banana", "cat", "car",         "card",  "care"};

    Solution sol;
    sol.build_trie(words);

    vector<string> prefixes = {"app", "ba", "car", "z", "c"};
    for (string& prefix : prefixes) {
        cout << "Prefix \"" << prefix << "\" -> [";
        auto results = sol.find_by_prefix(prefix);
        for (int i = 0; i < (int)results.size(); i++) {
            if (i)
                cout << ", ";
            cout << results[i];
        }
        cout << "]\n";
    }

    return 0;
}
