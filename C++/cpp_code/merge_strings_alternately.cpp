/*
1768. Merge Strings Alternately
https://leetcode.com/problems/merge-strings-alternately/

You are given two strings word1 and word2.
Merge the strings by adding letters in alternating order,
starting with word1. If a string is longer than the other,
append the additional letters onto the end of the merged string.

Return the merged string.

Example 1:
Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r
Example 2:
Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b
word2:    p   q   r   s
merged: a p b q   r   s
Example 3:
Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q
merged: a p b q c   d

Constraints:
1 <= word1.length, word2.length <= 100
word1 and word2 consist of lowercase English letters.
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
#include <bitset>
using namespace std;

class Solution {
public:
    string mergeAlternately(string w1, string w2) {
        int n = w1.size(), m = w2.size(), i = 0, j = 0;
        string res = "";
        while (i < n || j < m) {
            if (i < n)
                res.push_back(w1[i++]);
            if (j < m)
                res.push_back(w2[j++]);
        }
        return res;
    }
};