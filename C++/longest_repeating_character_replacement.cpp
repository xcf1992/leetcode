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
    int characterReplacement(string s, int k) {
        int result = 0;
        int start = 0;
        int maxCount = 0;
        vector<int> count(26, 0);
        for (int end = 0; end < s.size(); end++) {
            maxCount = max(maxCount, ++count[s[end] - 'A']);
            while (end - start + 1 - maxCount > k) {
                count[s[start++] - 'A'] -= 1;
            }
            result = max(result, end - start + 1);
        }
        return result;
    }
};