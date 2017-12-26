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
    int maxProduct(vector<string>& words) {
        int result = 0;
        vector<int> mask(words.size(), 0);
        for (int i = 0; i < words.size(); i++) {
            for (char c : words[i]) {
                mask[i] |= 1 << (c - 'a');
            }
        }

        for (int i = 0; i < words.size(); i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if (!(mask[i] & mask[j])) {
                    result = max(result, int(words[i].size() * words[j].size()));
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