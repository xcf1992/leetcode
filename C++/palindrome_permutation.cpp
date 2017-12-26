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
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> letter;
        for (int i = 0; i < s.size(); i++) {
            if (letter.find(s[i]) == letter.end()) {
                letter[s[i]] = 1;
            }
            else {
                letter[s[i]] += 1;
            }
        }

        int odd = 0;
        for (auto it = letter.begin(); it != letter.end(); it++) {
            if (it -> second % 2 == 1) {
                odd += 1;
            }
        }

        return odd <= 0;
    }
};

int main() {
    Solution s;
    return 0;
}