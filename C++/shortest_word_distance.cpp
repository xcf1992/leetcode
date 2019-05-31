/*
243. Shortest Word Distance
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
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

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int index1 = -1;
        int index2 = -1;
        int result = words.size();

        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                if (index2 != -1) {
                    result = min(result, i - index2);
                }
                index1 = i;
            }
            else if (words[i] == word2) {
                if (index1 != -1) {
                    result = min(result, i - index1);   
                }
                index2 = i;
            }
        }

        return result;
    }
};