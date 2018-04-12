/*
 Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.
 
 Example :
 Input:
 S = "abcde"
 words = ["a", "bb", "acd", "ace"]
 Output: 3
 Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
 Note:
 
 All words in words and S will only consists of lowercase letters.
 The length of S will be in the range of [1, 50000].
 The length of words will be in the range of [1, 5000].
 The length of words[i] will be in the range of [1, 50].
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
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<vector<int>> position(26, vector<int>());
        for (int i = 0; i < S.size(); i++) {
            position[S[i] - 'a'].push_back(i);
        }
        
        int result = 0;
        for (string word : words) {
            if (word.size() == 1 && !position[word[0] - 'a'].empty()) {
                result += 1;
                continue;
            }
            
            int curPos = 0;
            for (int i = 0; i < word.size(); i++) {
                if (position[word[i] - 'a'].empty()) {
                    break;
                }
                
                if (i == 0) {
                    curPos = position[word[i] - 'a'].front();
                }
                else {
                    bool find = false;
                    for (int newPos : position[word[i] - 'a']) {
                        if (newPos > curPos) {
                            find = true;
                            curPos = newPos;
                            break;
                        }
                    }
                    if (find) {
                        if (i == word.size() - 1) {
                            result += 1;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return result;
    }
};
