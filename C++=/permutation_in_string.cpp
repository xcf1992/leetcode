/*
567. Permutation in String
https://leetcode.com/problems/permutation-in-string/

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1.
In other words, one of the first string's permutations is the substring of the second string.

Example 1:
Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False

Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
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
private:
    bool allZero(vector<int>& count) {
        for (int num : count) {
            if (num != 0) {
                return false;
            }
        }
        return true;
    }
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        if (m > n) {
            return false;
        }

        vector<int> count(26, 0);
        for (int i = 0; i < m; i++) {
            count[s1[i] - 'a'] += 1;
            count[s2[i] - 'a'] -= 1;
        }
        if (allZero(count)) {
            return true;
        }

        for (int i = m; i < n; i++) {
            count[s2[i - m] - 'a'] += 1;
            count[s2[i] - 'a'] -= 1;
            if (allZero(count)) {
                return true;
            }
        }
        return false;
    }
};
