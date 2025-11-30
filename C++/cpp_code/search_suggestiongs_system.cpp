/*
1268. Search Suggestions System
https://leetcode.com/problems/search-suggestions-system/

Given an array of strings products and a string searchWord.
We want to design a system that suggests at most three product names from products after each character of searchWord is
typed. Suggested products should have common prefix with the searchWord. If there are more than three products with a
common prefix return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed.

Example 1:
Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]

Example 2:
Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]

Example 3:
Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]

Example 4:
Input: products = ["havana"], searchWord = "tatiana"
Output: [[],[],[],[],[],[],[]]

Constraints:
1 <= products.length <= 1000
1 <= Σ products[i].length <= 2 * 10^4
All characters of products[i] are lower-case English letters.
1 <= searchWord.length <= 1000
All characters of searchWord are lower-case English letters.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

struct TrieNode {
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    set<string> words;
};

class Solution {
private:
    TrieNode* root = new TrieNode();

    void addWord(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children[c - 'a'] == nullptr) {
                cur->children[c - 'a'] = new TrieNode();
            }
            cur = cur->children[c - 'a'];
            cur->words.insert(word);
        }
    }

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        for (string& product : products) {
            addWord(product);
        }

        int n = searchWord.size();
        vector<vector<string>> result(n);
        TrieNode* cur = root;
        for (int i = 0; i < n; ++i) {
            char c = searchWord[i];
            if (cur == nullptr or cur->children[c - 'a'] == nullptr) {
                break;
            }

            cur = cur->children[c - 'a'];
            for (string word : cur->words) {
                if (result[i].size() == 3) {
                    break;
                }
                result[i].push_back(word);
            }
        }
        return result;
    }
};

class Solution2 {
public:
    vector<vector<string>> suggestedProducts(vector<string>& ps, string word) {
        sort(begin(ps), end(ps));
        vector<vector<string>> res(word.size());
        for (auto l = 1; l <= word.size(); ++l) {
            auto w = word.substr(0, l);
            auto it = lower_bound(begin(ps), end(ps), w);
            for (; it != end(ps) && it->substr(0, l) == w && res[l - 1].size() < 3; ++it)
                res[l - 1].push_back(*it);
        }
        return res;
    }
};