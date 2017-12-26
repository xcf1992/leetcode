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

struct Trie {
    Trie* nodes[26] = {nullptr};
    int sum = 0;
};

class MapSum {
private:
    Trie* root;
    unordered_map<string, int> pairs;
public:
    /** Initialize your data structure here. */
    MapSum() {
        pairs.clear();
        root = new Trie();
    }

    void insert(string key, int val) {
        Trie* cur = root;
        for (int i = 0; i < key.size(); i++) {
            if (cur -> nodes[key[i] - 'a'] == nullptr) {
                cur -> nodes[key[i] - 'a'] = new Trie();
            }
            cur = cur -> nodes[key[i] - 'a'];
            cur -> sum += val - pairs[key];
        }
        pairs[key] = val;
    }

    int sum(string prefix) {
        Trie* cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (cur == nullptr) {
                break;
            }
            cur = cur -> nodes[prefix[i] - 'a'];
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