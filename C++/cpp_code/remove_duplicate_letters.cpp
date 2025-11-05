/*
316. Remove Duplicate Letters
Given a string which contains only lowercase letters,
remove duplicate letters so that every letter appear once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: "bcabc"
Output: "abc"

Example 2:
Input: "cbacdcbc"
Output: "acdb"
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
#include <map>
using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        for (char c: s) {
            count[c - 'a'] += 1;
        }

        vector<bool> visited(26, false);
        string result = "";
        for (char c: s) {
            count[c - 'a'] -= 1;
            if (visited[c - 'a']) {
                continue;
            }

            while (!result.empty() and c<result.back() and count[result.back() - 'a'] > 0
            )
            {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(c);
            visited[c - 'a'] = true;
        }
        return result;
    }
};