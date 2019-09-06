/*
677. Map Sum Pairs

Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer).
The string represents the key and the integer represents the value.
If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix,
and you need to return the sum of all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
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
    vector<TrieNode*> child = vector<TrieNode*>(26, nullptr);
    int sum = 0;
};

class MapSum {
private:
    TrieNode* root;
    unordered_map<string, int> pairs;
public:
    /** Initialize your data structure here.*/
    MapSum() {
        root = new TrieNode();
    }

    void insert(string key, int val) {
        TrieNode* cur = root;
        for (int i = 0; i < key.size(); i++) {
            if (cur -> child[key[i] - 'a'] == nullptr) {
                cur -> child[key[i] - 'a'] = new TrieNode();
            }
            cur = cur -> child[key[i] - 'a'];
            cur -> sum += val - pairs[key];
        }
        pairs[key] = val;
    }

    int sum(string prefix) {
        TrieNode* cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (cur == nullptr) {
                break;
            }
            cur = cur -> child[prefix[i] - 'a'];
        }
        return cur == nullptr ? 0 : cur -> sum;
    }
};
/**
* Your MapSum object will be instantiated and called as such:
* MapSum obj = new MapSum();
* obj.insert(key,val);
* int param_2 = obj.sum(prefix);
*/