/*
387. First Unique Character in a String

Given a string, find the first non-repeating character in it and return it's index.
If it doesn't exist, return -1.

Examples:
s = "leetcode"
return 0.

s = "loveleetcode",
return 2.

Note:
You may assume the string contain only lowercase letters.
*/
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
        int n = s.size();
        if (n == 0) {
            return -1;
        }
        if (n == 1) {
            return 0;
        }

        vector<int> character(26, -2);
        for (int i = 0; i < n; i++) {
            int pos = s[i] - 'a';
            if (character[pos] == -2) {
                character[pos] = i;
            } else {
                character[pos] = -1;
            }
        }

        int result = -1;
        for (int i = 0; i < character.size(); i++)
            if (character[i] >= 0) {
                if (result == -1) {
                    result = character[i];
                } else {
                    result = min(character[i], result);
                }
            }
        return result;
    }
};