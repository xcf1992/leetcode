/*
49. Group Anagrams
https://leetcode.com/problems/group-anagrams/

Given an array of strings, group anagrams together.

Example:
Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:
All inputs will be in lowercase.
The order of your output does not matter.
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
using namespace std;

class Solution {
private:
    string getMask(string& word) {
        vector<int> count(26, 0);
        for (char c : word) {
            count[c - 'a'] += 1;
        }

        string mask = "";
        for (int i = 0; i < 26; ++i)
            if (count[i] != 0) {
                mask += string(1, 'a' + i) + to_string(count[i]);
            }
        return mask;
    }

public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> memo;
        for (string& word : strs) {
            memo[getMask(word)].push_back(word);
        }

        vector<vector<string>> result;
        for (auto& it : memo) {
            result.push_back(it.second);
        }
        return result;
    }
};