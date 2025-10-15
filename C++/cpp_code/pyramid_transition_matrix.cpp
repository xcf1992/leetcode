/*
756. Pyramid Transition Matrix
https://leetcode.com/problems/pyramid-transition-matrix/

We are stacking blocks to form a pyramid.
Each block has a color which is a one letter string.
We are allowed to place any color block C on top of two adjacent blocks of colors A and B,
if and only if ABC is an allowed triple.

We start with a bottom row of bottom,
represented as a single string.
We also start with a list of allowed triples allowed.
Each allowed triple is represented as a string of length 3.

Return true if we can build the pyramid all the way to the top, otherwise false.

Example 1:
Input: bottom = "BCD", allowed = ["BCG", "CDE", "GEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  G   E
 / \ / \
B   C   D
We are allowed to place G on top of B and C because BCG is an allowed triple.
Similarly, we can place E on top of C and D, then A on top of G and E.

Example 2:
Input: bottom = "AABA", allowed = ["AAA", "AAB", "ABA", "ABB", "BAC"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.

Note:
bottom will be a string with length in range [2, 8].
allowed will have length in range [0, 200].
Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.
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
using namespace std;

class Solution {
private:
    bool dfs(string curRow, string nextRow, int start, vector<vector<vector<char>>>& cache) {
        if (curRow.size() == 1) {
            return true;
        }

        if (start == curRow.size() - 1) {
            return dfs(nextRow, "", 0, cache);
        }

        for (char c : cache[curRow[start] - 'A'][curRow[start + 1] - 'A']) {
            nextRow.push_back(c);
            if (dfs(curRow, nextRow, start + 1, cache)) {
                return true;
            }
            nextRow.pop_back();
        }
        return false;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        vector<vector<vector<char>>> cache(26, vector<vector<char>>(26, vector<char>({})));
        for (string& word : allowed) {
            cache[word[0] - 'A'][word[1] - 'A'].push_back(word[2]);
        }
        return dfs(bottom, "", 0, cache);
    }
};

class Solution1 {
private:
    bool dfs(string bottom, string curRow, int index, unordered_multimap<string, char> validBlock) {
        if (index == curRow.size()) {
            if (curRow.size() == 1) {
                return true;
            }
            string nextRow(curRow.size() - 1, 'Z');
            return dfs(curRow, nextRow, 0, validBlock);
        }

        string prefix(2, 'Z');
        prefix[0] = bottom[index];
        prefix[1] = bottom[index + 1];
        auto blocks = validBlock.equal_range(prefix);
        for (auto it = blocks.first; it != blocks.second; it++) {
            curRow[index] = it -> second;
            if (dfs(bottom, curRow, index + 1, validBlock)) {
                return true;
            }
        }
        return false;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_multimap<string, char> validBlock;
        for (string block : allowed) {
            validBlock.insert(pair<string, int>(block.substr(0, 2), block.back()));
        }
        string curRow(bottom.size() - 1, 'Z');
        return dfs(bottom, curRow, 0, validBlock);
    }
};


