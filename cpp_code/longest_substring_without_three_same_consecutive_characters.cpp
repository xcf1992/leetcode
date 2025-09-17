/*
https://www.geeksforgeeks.org/longest-substring-such-that-no-three-consecutive-characters-are-same/
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
    int longestSubstringLength(string s) {
        int n = s.size();
        if (n < 3) {
            return n;
        }

        int result = 2;
        int cur = 2;
        for (int i = 2; i < n; ++i) {
            if (s[i] != s[i - 1] or s[i] != s[i - 2]) {
                cur += 1;
            }
            else {
                result = max(result, cur);
                cur = 2;
            }
        }
        return max(result, cur);
    }
};
