/*
1079. Letter Tile Possibilities
https://leetcode.com/problems/letter-tile-possibilities/

You have a set of tiles,
where each tile has one letter tiles[i] printed on it.
Return the number of possible non-empty sequences of letters you can make.

Example 1:
Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".

Example 2:
Input: "AAABBC"
Output: 188

Note:
1 <= tiles.length <= 7
tiles consists of uppercase English letters.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    void generate(vector<string> &result, unordered_map<char, int> &count, string current, int len) {
        if (current != "") {
            result.push_back(current);
        }
        if (current.size() == len) {
            return;
        }

        for (auto it = count.begin(); it != count.end(); ++it) {
            if (it->second > 0) {
                it->second -= 1;
                current.push_back(it->first);
                generate(result, count, current, len);
                current.pop_back();
                it->second += 1;
            }
        }
    }

public:
    int numTilePossibilities(string tiles) {
        unordered_map<char, int> count;
        for (char c: tiles) {
            count[c] += 1;
        }

        vector<string> result;
        generate(result, count, "", tiles.size());
        return result.size();
    }
};