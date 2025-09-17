/*
1202. Smallest String With Swaps
https://leetcode.com/problems/smallest-string-with-swaps/

You are given a string s,
and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given pairs any number of times.
Return the lexicographically smallest string that s can be changed to after using the swaps.

Example 1:
Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"

Example 2:
Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"

Example 3:
Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination:
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"

Constraints:
1 <= s.length <= 10^5
0 <= pairs.length <= 10^5
0 <= pairs[i][0], pairs[i][1] < s.length
s only contains lower case English letters.
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
#include <set>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    int find(int num, vector<int>& parent) {
        if (parent[num] != num) {
            parent[num] = find(parent[num], parent);
        }
        return parent[num];
    }
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        for (vector<int>& pair : pairs) {
            int pu = find(pair[0], parent);
            int pv = find(pair[1], parent);
            if (pu != pv) {
                parent[pu] = pv;
            }
        }

        vector<vector<int>> component(n);
        for (int i = 0; i < n; ++i) {
            component[find(i, parent)].push_back(i); // the sequence of id in each component will be in increasing order
        }

        for (vector<int>& c : component) if (!c.empty()) {
            string temp = "";
            for (int id : c) {
                temp += s[id];
            }
            sort(temp.begin(), temp.end());

            for (int j = 0; j < c.size(); ++j) {
                s[c[j]] = temp[j];
            }
        }
        return s;
    }
};
