/*
https://www.geeksforgeeks.org/lexicographically-smallest-string-formed-by-removing-at-most-one-character/
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
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    string smallestString(string s) {
        int n = s.size();
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] <= s[i + 1]) {
                continue;
            }
            return s.substr(0, i) + s.substr(i + 1);
        }
        return s.substr(0, n - 1);
    }
};