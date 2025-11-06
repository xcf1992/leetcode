#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> letters(26, 0);
        for (int i = 0; i < magazine.size(); i++) {
            letters[magazine[i] - 'a'] += 1;
        }

        for (int i = 0; i < ransomNote.size(); i++) {
            int pos = ransomNote[i] - 'a';
            letters[pos] -= 1;
            if (letters[pos] < 0) {
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