/*
 269. Alien Dictionary
 There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.
 
 Example 1:
 
 Input:
 [
 "wrt",
 "wrf",
 "er",
 "ett",
 "rftt"
 ]
 
 Output: "wertf"
 Example 2:
 
 Input:
 [
 "z",
 "x"
 ]
 
 Output: "zx"
 Example 3:
 
 Input:
 [
 "z",
 "x",
 "z"
 ]
 
 Output: ""
 
 Explanation: The order is invalid, so return "".
 Note:
 
 You may assume all letters are in lowercase.
 You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
 If the order is invalid, return an empty string.
 There may be multiple valid order of letters, return any one of them is fine.
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.empty()) {
            return "";
        }
        
        unordered_map<char, int> indegree;
        for (string word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }
        
        unordered_map<char, unordered_set<char>> graph;
        for (int i = 0; i < words.size() - 1; i++) {
            string cur = words[i];
            string nex = words[i + 1];
            int length = min(cur.size(), nex.size());
            for (int j = 0; j < length; j++) {
                if (cur[j] != nex[j]) {
                    if (graph[cur[j]].find(nex[j]) == graph[cur[j]].end()) {
                        graph[cur[j]].insert(nex[j]);
                        indegree[nex[j]] += 1;
                    }
                    break;
                }
            }
        }
        
        string result = "";
        queue<char>bfs;
        for (auto& it : indegree) {
            if (it.second == 0) {
                bfs.push(it.first);
            }
        }
        while (!bfs.empty()) {
            char cur = bfs.front();
            bfs.pop();
            result.push_back(cur);
            
            if (graph[cur].size() != 0) {
                for (char c : graph[cur]) {
                    indegree[c] -= 1;
                    if (indegree[c] == 0) {
                        bfs.push(c);
                    }
                }
            }
        }
        return result.size() == indegree.size() ? result : "";
    }
};
