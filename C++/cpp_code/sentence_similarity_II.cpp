/*
 737. Sentence Similarity II
 Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs,
 determine if two sentences are similar.

 For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the
 similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

 Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good"
 are similar, then "great" and "fine" are similar.

 Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being
 similar.

 Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs =
 [] are similar, even though there are no specified similar word pairs.

 Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can
 never be similar to words2 = ["doubleplus","good"].

 Note:

 The length of words1 and words2 will not exceed 1000.
 The length of pairs will not exceed 2000.
 The length of each pairs[i] will be 2.
 The length of each words[i] and pairs[i][j] will be in the range [1, 20].
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
using namespace std;

class Solution {
private:
    unordered_map<string, string> match;

    string find(string word) {
        if (match.find(word) == match.end()) {
            match[word] = word;
        }
        return word == match[word] ? word : find(match[word]);
    }

public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>> pairs) {
        if (words1.size() != words2.size()) {
            return false;
        }

        for (vector<string>& pair : pairs) {
            string parent1 = find(pair[0]);
            string parent2 = find(pair[1]);

            if (parent1 != parent2) {
                match[parent1] = parent2;
            }
        }

        for (int i = 0; i < words1.size(); i++) {
            if (words1[i] != words2[i]) {
                if (find(words1[i]) != find(words2[i])) {
                    return false;
                }
            }
        }
        return true;
    }
};