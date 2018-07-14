/*
 A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".
 
 Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.
 
 For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.
 
 Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.
 
 Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.
 
 Note:
 
 Starting point is assumed to be valid, so it might not be included in the bank.
 If multiple mutations are needed, all mutations during in the sequence must be valid.
 You may assume start and end string is not the same.
 
 
 Example 1:
 
 start: "AACCGGTT"
 end:   "AACCGGTA"
 bank: ["AACCGGTA"]
 
 return: 1
 
 
 Example 2:
 
 start: "AACCGGTT"
 end:   "AAACGGTA"
 bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]
 
 return: 2
 
 
 Example 3:
 
 start: "AAAAACCC"
 end:   "AACCCCCC"
 bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]
 
 return: 3
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
using namespace std;

class Solution { // DFS
private:
    bool mutatedFrom(string from, string to) {
        int result = 0;
        for (int i = 0; i < from.size(); i++) {
            if (from[i] != to[i]) {
                result += 1;
                if (result > 1) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void dfs(string cur, string end, vector<string>& bank, unordered_map<string, bool>& visited, int count, int& result) {
        if (cur == end) {
            result = min(count, result);
        }
        
        for (string gene : bank) {
            if (!visited[gene] && mutatedFrom(cur, gene)) {
                visited[gene] = true;
                dfs(gene, end, bank, visited, count + 1, result);
                visited[gene] = false;
            }
        }
    }
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, bool> visited;
        for (string gene : bank) {
            visited[gene] = false;
        }
        int result = INT_MAX;
        visited[start] = true;
        dfs(start, end, bank, visited, 0, result);
        return result == INT_MAX ? -1 : result;
    }
};

class Solution1 { // BFS
private:
    bool mutatedFrom(string from, string to) {
        int result = 0;
        for (int i = 0; i < from.size(); i++) {
            if (from[i] != to[i]) {
                result += 1;
                if (result > 1) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, bool> visited;
        for (string gene : bank) {
            visited[gene] = false;
        }
        
        queue<string> bfs;
        bfs.push(start);
        visited[start] = true;
        int step = 0;
        while (!bfs.empty()) {
            int length = bfs.size();
            for (int i = 0; i < length; i++) {
                string cur = bfs.front();
                bfs.pop();
                
                if (cur == end) {
                    return step;
                }
                
                for (string gene : bank) {
                    if (!visited[gene] && mutatedFrom(cur, gene)) {
                        bfs.push(gene);
                        visited[gene] = true;
                    }
                }
            }
            step += 1;
        }
        return -1;
    }
};
