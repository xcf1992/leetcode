/*
187. Repeated DNA Sequences
https://leetcode.com/problems/repeated-dna-sequences/

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
for example: "ACGAATTCCG".
When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

Example:
Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC", "CCCCCAAAAA"]
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
#include <numeric>
using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        if (n < 10) {
            return {};
        }
        unordered_map<int, int> letter;
        letter[0] = 0;
        letter[2] = 1;
        letter[6] = 2;
        letter[19] = 3;

        int num = 0;
        unordered_map<int, int> visited;
        for (int i = 0; i < 10; ++i) {
            num <<= 2;
            int cur = letter[s[i] - 'A'];
            num |= cur;
        }
        visited[num] = 1;

        vector<string> result;
        for (int i = 10; i < n; ++i) {
            num <<= 2;
            num &= 0x000fffff;
            num |= letter[s[i] - 'A'];
            if (visited[num] == 1) {
                result.push_back(s.substr(i - 10 + 1, 10));
            }
            visited[num] += 1;
        }
        return result;
    }
};
