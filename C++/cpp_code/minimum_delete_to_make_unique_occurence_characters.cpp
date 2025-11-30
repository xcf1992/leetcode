/*
Given a string S consisting of N lowercase letters,
returns the minumum number of letters that must be deleted to obtain a word
in‍‍‍‍‌‌‌‌‌‌‍‍‌‍‌‍‌‌‌ which every letter occurs a unique number of times.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int minimumDeleteToMakeUnique(string s) {
        int n = s.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> occurence(26, 0);
        for (char c : s) {
            occurence[c - 'a'] += 1;
        }
        vector<int> count(n + 1, 0);
        for (int i = 0; i < 26; ++i) {
            if (occurence[i] != 0) {
                count[occurence[i]] += 1;
            }
        }

        int result = 0;
        for (int i = n; i > 0; --i) {
            if (count[i] > 1) {
                result += count[i] - 1;
                count[i - 1] += count[i] - 1;
            }
        }
        return result;
    }
};
