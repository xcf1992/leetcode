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
    bool isSubsequence(string s, string t) {
        int sPtr = 0;
        int tPtr = 0;
        while (sPtr < s.size() && tPtr < t.size()) {
            if (s[sPtr] == t[tPtr]) {
                sPtr++;
            }
            tPtr++;
        }
        return sPtr == s.size();
    }
public:
    string findLongestWord(string s, vector<string>& d) {
        string result = "";
        for (string word : d) {
            if (isSubsequence(word, s)) {
                if (word.size() > result.size()) {
                    result = word;
                }
                else if (word.size() == result.size() && word < result) {
                    result = word;
                }
            }
        }
        return result;
    }
};