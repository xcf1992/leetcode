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

class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> prefix;
        string result;
        for (string word : words) {
            if (word.size() == 1 || prefix.find(word.substr(0, word.size() - 1)) != prefix.end()) {
                result = word.size() > result.size() ? word : result;
                prefix.insert(word);
            }
        }
        return result;
    }
};
