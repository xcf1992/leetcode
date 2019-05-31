/*
890. Find and Replace Pattern

 You have a list of words and a pattern, and you want to know which words in words matches the pattern.
 
 A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
 
 (Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.)
 
 Return a list of the words in words that match the given pattern.
 
 You may return the answer in any order.
 
 
 
 Example 1:
 
 Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
 Output: ["mee","aqq"]
 Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}.
 "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
 since a and b map to the same letter.
 
 
 Note:
 
 1 <= words.length <= 50
 1 <= pattern.length = words[i].length <= 20
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    bool check(string word, string pattern) {
        unordered_map<char, char> w2p;
        unordered_map<char, char> p2w;
        for (int i = 0; i < word.size(); i++) {
            if (w2p.find(word[i]) == w2p.end()) {
                w2p[word[i]] = pattern[i];
            }
            if (p2w.find(pattern[i]) == p2w.end()) {
                p2w[pattern[i]] = word[i];
            }
            if (w2p[word[i]] != pattern[i] || p2w[pattern[i]] != word[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool matched(string word, string pattern) {
        if (word.size() % pattern.size() != 0) {
            return false;
        }

        while (!word.empty()) {
            if (!check(word.substr(0, pattern.size()), pattern)) {
                return false;
            }
            word = word.substr(pattern.size());
        }
        return true;
    }
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> result;
        for (string word : words) {
            if (matched(word, pattern)) {
                result.push_back(word);
            }
        }
        return result;
    }
};
