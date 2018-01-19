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
using namespace std;

struct Comp {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
        return b.second > a.second || (a.second == b.second && b.first < a.first);
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> result;
        unordered_map<string, int> frequency;
        for (string word : words) {
            frequency[word] += 1;
        }
        
        priority_queue<pair<string, int>, vector<pair<string, int>>, Comp> sortWords;
        for (const auto& freq : frequency) {
            sortWords.push(freq);
        }
        
        while (result.size() < k && !sortWords.empty()) {
            result.push_back(sortWords.top().first);
            sortWords.pop();
        }
        return result;
    }
};
