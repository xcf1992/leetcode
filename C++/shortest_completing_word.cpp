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
private:
    bool complete(string word, unordered_map<char, int> letters, int plateSize) {
        for (int i = 0; i < word.size(); i++) {
            char letter = tolower(word[i]);
            if (letters.find(letter) != letters.end() && letters[letter] > 0) {
                plateSize -= 1;
                letters[letter] -= 1;
            }
        }
        return plateSize == 0;
    }
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        unordered_map<char, int> letters;
        int plateSize = 0;
        for (int i = 0; i < licensePlate.size(); i++) {
            char letter = tolower(licensePlate[i]);
            if (letter >= 'a' && letter <= 'z') {
                letters[letter] += 1;
                plateSize += 1;
            }
        }
        
        int maxLength = -1;
        string result;
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            if (complete(word, letters, plateSize)) {
                if (maxLength == -1 || maxLength > word.size()) {
                    maxLength = word.size();
                    result = word;
                }
            }
        }
        
        return result;
    }
};
