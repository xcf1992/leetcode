/*
 1032. Stream of Characters

 Implement the StreamChecker class as follows:

 StreamChecker(words): Constructor, init the data structure with the given words.
 query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.


 Example:

 StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
 streamChecker.query('a');          // return false
 streamChecker.query('b');          // return false
 streamChecker.query('c');          // return false
 streamChecker.query('d');          // return true, because 'cd' is in the wordlist
 streamChecker.query('e');          // return false
 streamChecker.query('f');          // return true, because 'f' is in the wordlist
 streamChecker.query('g');          // return false
 streamChecker.query('h');          // return false
 streamChecker.query('i');          // return false
 streamChecker.query('j');          // return false
 streamChecker.query('k');          // return false
 streamChecker.query('l');          // return true, because 'kl' is in the wordlist


 Note:

 1 <= words.length <= 2000
 1 <= words[i].length <= 2000
 Words will only consist of lowercase English letters.
 Queries will only consist of lowercase English letters.
 The number of queries is at most 40000.
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class TrieNode {
public:
    bool isWord = false;
    vector<TrieNode*> next = vector<TrieNode*>(26, nullptr);

    TrieNode(bool word = false): isWord(word) {}
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string& word) {
        TrieNode* cur = root;
        for (int i = word.size() - 1; i >= 0 ; --i) {
            int pos = word[i] - 'a';
            if (cur -> next[pos] == nullptr) {
                cur -> next[pos] = new TrieNode;
            }
            cur = cur -> next[pos];
        }
        cur -> isWord = true;
    }

    bool find(string& word) {
        TrieNode* cur = root;
        for (int i = word.size() - 1; i >= 0; --i) {
            int pos = word[i] - 'a';
            cur = cur -> next[pos];
            if (cur == nullptr) {
                return false;
            }
            if (cur -> isWord) {
                return true;
            }
        }
        return false;
    }
};

class StreamChecker {
private:
    Trie trie;
    string curWord = "";
public:
    StreamChecker(vector<string>& words) {
        for (string& word : words) {
            trie.insert(word);
        }
    }

    bool query(char letter) {
        curWord.push_back(letter);
        return trie.find(curWord);
    }
};

/*
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
*/
