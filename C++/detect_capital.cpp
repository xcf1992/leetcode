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
 * 1. All letters in this word are capitals, like "USA".
 * 2. All letters in this word are not capitals, like "leetcode".
 * 3. Only the first letter in this word is capital if it has more than one letter, like "Google".
*/
class Solution {
public:
    bool detectCapitalUse(string word) {
        bool all_capital = false;

        if (word[0] >= 'a' && word[0] <= 'z') {
            all_capital = false;
        }
        else {
            all_capital = true;
        }

        for (int i = 1; i < word.size(); i++) {
            char letter = word[i];

            if (i == 1) {
                if (letter <= 'z' && letter >= 'a') {
                    all_capital = false;
                }
                else if (!all_capital) { // AA
                    return false;
                }
            }
            else {
                if (letter <= 'z' && letter >= 'a') { // ..a
                    if (all_capital) {
                        return false;
                    }
                }
                else if (!all_capital) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution s;
    return 0;
}
