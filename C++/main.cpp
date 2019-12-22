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
#include <map>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        if (n < minSize) {
            return 0;
        }

        unordered_map<string, int> occurrence;
        vector<int> letter(26, 0);
        int count = 0;
        int left = 0;
        int result = 0;
        for (int right = 0; right < n; ++right) {
            letter[s[right]] += 1;
            if (letter[s[right]] == 1) {
                count += 1;
            }

            if (right - left + 1 > minSize) {
                letter[s[left]] -= 1;
                if (letter[s[left]] == 0) {
                    count -= 1;
                }
                left += 1;
            }

            int len = right - left + 1;
            if (len == minSize and count <= maxLetters) {
                string sub = s.substr(left, len);
                occurrence[sub] += 1;
                result = max(result, occurrence[sub]);
            }
        }
        return result;
    }
};

int main() {
    vector<vector<int>> matrix({{-73,61,43,-48,-36},{3,30,27,57,10},{96,-76,84,59,-15},{5,-49,76,31,-7},{97,91,61,-46,67}});
    
    Solution s;
    s.maxFreq("aababcaab", 2, 3, 4);
}
