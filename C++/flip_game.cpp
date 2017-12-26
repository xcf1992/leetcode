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
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> result;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '+' && s[i - 1] == '+') {
                string temp = s;
                temp[i] = '-';
                temp[i - 1] = '-';
                result.push_back(temp);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}