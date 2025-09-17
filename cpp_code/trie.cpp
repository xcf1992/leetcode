#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    vector<TrieNode *> next;
    bool end;

    TrieNode() {
        next.resize(26, nullptr);
        end = false;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
        root->end = true;
    }

    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode *cur = root;
        for (int i = 0; i < s.size(); i++) {
            int pos = s[i] - 'a';
            if (cur->next[pos] == nullptr) {
                cur->next[pos] = new TrieNode();
            }
            cur = cur->next[pos];
        }
        cur->end = true;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode *cur = root;
        for (int i = 0; i < key.size(); i++) {
            int pos = key[i] - 'a';
            if (cur->next[pos] == nullptr) {
                return false;
            }
            cur = cur->next[i];
        }
        return cur->end;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            int pos = prefix[i] - 'a';
            if (cur->next[pos] == nullptr) {
                return false;
            }
            cur = cur->next[pos];
        }
        return true;
    }

private:
    TrieNode* root;
};

int main() {
	Trie trie;
	trie.insert("hello");
	trie.search("hell");
	trie.search("helloa");
	trie.search("hello");
	trie.startsWith("hell");
	trie.startsWith("helloa");
	trie.startsWith("hello");
}