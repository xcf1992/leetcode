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
    string frequencySort(string s) {
        unordered_map<int, vector<char>> frequency;
        unordered_map<char, int> letter;
        for (auto c : s) {
            letter[c] += 1;
        }

        for (auto it : letter) {
            frequency[it.second].push_back(it.first);
        }

        string result = "";
        int i = s.size();
        while (result.size() < s.size()) {
            while (frequency.find(i) == frequency.end()) {
                i -= 1;
            }

            for (auto c : frequency[i]) {
                for (int j = 0; j < i; j++) {
                    result += c;
                }
            }
            i -= 1;
        }
        return result;
    }
};

int main() {
    Solution s;
    s.frequencySort("tree");
    return 0;
}
