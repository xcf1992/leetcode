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
    int firstUniqChar(string s) {
        if (s.empty()) {
            return -1;
        }
        if (s.size() == 1) {
            return 0;
        }
        vector<int> character (26, -2);
        for (int i = 0; i < s.size(); i++) {
            int pos = s[i] - 'a';
            if (character[pos] == -2) {
                character[pos] = i;
            }
            else {
                character[pos] = -1;
            }
        }

        int result = -1;
        for (int i = 0; i < character.size(); i++) {
            if (character[i] >= 0) {
                if (result == -1) {
                    result = character[i];
                }
                else {
                    result = min(character[i], result);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    cout << s.firstUniqChar("aa") << endl;
    return 0;
}