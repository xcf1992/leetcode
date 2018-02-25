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

/*
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.


*/
class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int n = words.size();
        int dist = INT_MAX;
        int i1 = n;
        int i2 = 0 - n;
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                i1 = i;
            }
            if (words[i] == word2) {
                if (word1 == word2) {
                    i1 = i2;
                }
                i2 = i;
            }
            dist = min(dist, abs(i1 - i2));
        }
        return dist;
    }
};