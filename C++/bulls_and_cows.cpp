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
    string getHint(string secret, string guess) {
        int bulls = 0;
        int cows = 0;
        vector<int> count(10, 0);

        for (int i = 0; i < secret.size(); i++) {
            count[secret[i] - '0'] += 1;
            if (secret[i] = guess[i]) {
                bulls += 1;
            }
        }

        for (int i = 0; i < guess.size(); i++) {
            if (count[guess[i] - '0']) {
                cows += 1;
                count[guess[i] - '0'] -= 1;
            }
        }

        return to_string(bulls) + "A" + to_string(cows - bulls) + "B";
    }
};

int main() {
    Solution s;
    return 0;
}