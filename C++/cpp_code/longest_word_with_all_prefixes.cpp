/*
https://leetcode.com/problems/longest-word-with-all-prefixes/description/
1858. Longest Word With All Prefixes

Given an array of strings words, find the longest string in words such that every prefix of it is also in words.

For example, let words = ["a", "app", "ap"]. The string "app" has prefixes "ap" and "a", all of which are in words.
Return the string described above. If there is more than one string with the same length, return the lexicographically
smallest one, and if no string exists, return "".



Example 1:

Input: words = ["k","ki","kir","kira", "kiran"]
Output: "kiran"
Explanation: "kiran" has prefixes "kira", "kir", "ki", and "k", and all of them appear in words.
Example 2:

Input: words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: Both "apple" and "apply" have all their prefixes in words.
However, "apple" is lexicographically smaller, so we return that.
Example 3:

Input: words = ["abc", "bc", "ab", "qwe"]
Output: ""


Constraints:

1 <= words.length <= 105
1 <= words[i].length <= 105
1 <= sum(words[i].length) <= 105
words[i] consists only of lowercase English letters.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
#include <numeric>
using namespace std;

// we can also use trie, and insert from shortest word to longest one
class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> dict(words.begin(), words.end());
        sort(words.begin(), words.end(),
             [](string& s1, string& s2) { return s1.size() > s2.size() || (s1.size() == s2.size() && s1 < s2); });

        string rst = "";
        for (string& word : words) {
            int len = word.size();
            bool all_exist = true;
            for (int i = 1; i < len; i++) {
                string prefix = word.substr(0, i);
                if (dict.find(prefix) == dict.end()) {
                    all_exist = false;
                    break;
                }
            }
            if (all_exist) {
                rst = word;
                break;
            }
        }
        return rst;
    }
};