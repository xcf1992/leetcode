/*
 438. Find All Anagrams in a String
 Given a string s and a non-empty string p,
 find all the start indices of p's anagrams in s.

 Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

 The order of output does not matter.

 Example 1:

 Input:
 s: "cbaebabacd" p: "abc"

 Output:
 [0, 6]

 Explanation:
 The substring with start index = 0 is "cba", which is an anagram of "abc".
 The substring with start index = 6 is "bac", which is an anagram of "abc".
 Example 2:

 Input:
 s: "abab" p: "ab"

 Output:
 [0, 1, 2]

 Explanation:
 The substring with start index = 0 is "ab", which is an anagram of "ab".
 The substring with start index = 1 is "ba", which is an anagram of "ab".
 The substring with start index = 2 is "ab", which is an anagram of "ab".
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
#include <set>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return {};
        }

        vector<int> target(26, 0);
        for (char c : p) {
            target[c - 'a'] += 1;
        }

        vector<int> window(26, 0);
        for (int i = 0; i < p.size() - 1; i++) {
            window[s[i] - 'a'] += 1;
        }
        
        vector<int> result;
        for (int i = p.size() - 1; i < s.size(); i++) {
            window[s[i] - 'a'] += 1;

            bool found = true;
            for (int i = 0; i < 26; i++) {
                if (target[i] != window[i]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                result.push_back(i - p.size() + 1);
            }

            window[s[i - p.size() + 1] - 'a'] -= 1;
        }
        return result;
    }
};
