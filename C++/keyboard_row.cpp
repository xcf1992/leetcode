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
    unordered_map<char, int> letters {
        { 'q', 1 }, { 'w', 1 }, { 'e', 1 }, { 'r', 1 }, { 't', 1 }, { 'y', 1 }, { 'u', 1 }, { 'i', 1 }, { 'o', 1 }, { 'p', 1 },
        { 'a', 2 }, { 's', 2 }, { 'd', 2 }, { 'f', 2 }, { 'g', 2 }, { 'h', 2 }, { 'j', 2 }, { 'k', 2 }, { 'l', 2 },
        { 'z', 3 }, { 'x', 3 }, { 'c', 3 }, { 'v', 3 }, { 'b', 3 }, { 'n', 3 }, { 'm', 3 },
        { 'Q', 1 }, { 'W', 1 }, { 'E', 1 }, { 'R', 1 }, { 'T', 1 }, { 'Y', 1 }, { 'U', 1 }, { 'I', 1 }, { 'O', 1 }, { 'P', 1 },
        { 'A', 2 }, { 'S', 2 }, { 'D', 2 }, { 'F', 2 }, { 'G', 2 }, { 'H', 2 }, { 'J', 2 }, { 'K', 2 }, { 'L', 2 },
        { 'Z', 3 }, { 'X', 3 }, { 'C', 3 }, { 'V', 3 }, { 'B', 3 }, { 'N', 3 }, { 'M', 3 }
    };

    bool validate(string word) {
        int row = letters[word[0]];

        for (int i = 1; i < word.size(); i++) {
            if (letters[word[i]] != row) {
                return false;
            }
        }

        return true;
    }

public:
    vector<string> findWords(vector<string>& words) {
        vector<string> result;

        for (int i = 0; i < words.size(); i++) {
            if (validate(words[i])) {
                result.push_back(words[i]);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}