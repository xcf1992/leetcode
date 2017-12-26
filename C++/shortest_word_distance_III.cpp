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
    int calculate(vector<string>& words, string word1, string word2) {
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
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        if (word2 != word1) {
            return calculate(words, word1, word2);
        }

        int result = words.size();
        int index1 = -1;
        int index2 = -1;
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                if (index1 == -1) {
                    index1 = i;
                }
                else if (index2 == -1) {
                    index2 = index1;
                    index1 = i;
                    result = index1 - index2;
                }
                else {
                    index2 = index1;
                    index1 = i;
                    result = min(result, index1 - index2);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}