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
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        vector<int> letters(26, 0);
        for (int i = 0; i < s.size(); i++) {
            letters[s[i] - 'a'] += 1;
            letters[t[i] - 'a'] -= 1;
        }

        for (int i = 0; i < letters.size(); i++) {
            if (letters[i] != 0) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Solution s;
    return 0;
}