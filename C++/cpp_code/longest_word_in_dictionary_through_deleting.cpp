/*
524. Longest Word in Dictionary through Deleting
https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/

Given a string and a string dictionary,
find the longest string in the dictionary that can be formed by deleting some characters of the given string.
If there are more than one possible results,
return the longest word with the smallest lexicographical order.
If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]
Output:
"apple"

Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]
Output:
"a"

Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.
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
    bool isSubsequence(string& target, string& source) {
        int sPtr = 0;
        int tPtr = 0;
        while (sPtr < source.size() and tPtr < target.size()) {
            if (source[sPtr] == target[tPtr]) {
                tPtr++;
            }
            sPtr++;
        }
        return tPtr == target.size();
    }

public:
    string findLongestWord(string s, vector<string>& d) {
        string result = "";
        for (string word : d) {
            if (isSubsequence(word, s)) {
                if (word.size() > result.size()) {
                    result = word;
                } else if (word.size() == result.size() and word < result) {
                    result = word;
                }
            }
        }
        return result;
    }
};
