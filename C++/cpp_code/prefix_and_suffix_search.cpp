/*
745. Prefix and Suffix Search

Given many words, words[i] has weight i.

Design a class WordFilter that supports one function,
WordFilter.f(String prefix, String suffix).
It will return the word with given prefix and suffix with maximum weight.
If no word exists, return -1.

Examples:
Input:
WordFilter(["apple"])
WordFilter.f("a", "e") // returns 0
WordFilter.f("b", "") // returns -1

Note:
words has length in range [1, 15000].
For each test case, up to words.length queries WordFilter.f may be made.
words[i] has length in range [1, 10].
prefix, suffix have lengths in range [0, 10].
words[i] and prefix, suffix queries consist of lowercase letters only.
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;
/*
For a word like "test", consider "#test", "t#test", "st#test", "est#test", "test#test".
Then if we have a query like prefix = "te", suffix = "t",
we can find it by searching for something we've inserted starting with "t#te".
*/
struct Node {
    int weight;
    vector<Node*> next;

    Node() {
        weight = -1;
        next.resize(27, nullptr);
    }
};

class WordFilter {
private:
    Node* root;

    void insert(string word, int weight) {
        Node* cur = root;
        for (char ch : word) {
            int pos = ch - 'a';
            if (cur->next[pos] == nullptr) {
                cur->next[pos] = new Node();
            }
            cur = cur->next[pos];
            cur->weight = weight;
        }
    }

    int search(string word) {
        Node* cur = root;
        for (char ch : word) {
            int pos = ch - 'a';
            if (cur->next[pos] == nullptr) {
                return -1;
            }
            cur = cur->next[pos];
        }
        return cur->weight;
    }

public:
    WordFilter(vector<string> words) {
        root = new Node();
        for (int i = 0; i < words.size(); i++) {
            int len = words[i].size();
            for (int j = 0; j <= len; j++) {
                // '{' is the next character after lower case 'z' in ascii
                insert(words[i].substr(len - j) + "{" + words[i], i);
            }
        }
    }

    int f(string prefix, string suffix) {
        return search(suffix + "{" + prefix);
    }
};

/*
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter obj = new WordFilter(words);
 * int param_1 = obj.f(prefix,suffix);
 */