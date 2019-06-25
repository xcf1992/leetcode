/*
 854. K-Similar Strings
 Strings A and B are K-similar (for some non-negative integer K)
 if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

 Given two anagrams A and B, return the smallest K for which A and B are K-similar.

 Example 1:

 Input: A = "ab", B = "ba"
 Output: 1
 Example 2:

 Input: A = "abc", B = "bca"
 Output: 2
 Example 3:

 Input: A = "abac", B = "baca"
 Output: 2
 Example 4:

 Input: A = "aabc", B = "abca"
 Output: 2
 Note:

 1 <= A.length == B.length <= 20
 A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
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

class Solution { // DFS with memo
private:
    unordered_map<string, int> memo;

    int dfs(string& cur, string& target) {
        if (memo.find(cur) != memo.end()) {
            return memo[cur];
        }

        int pos = 0;
        int len = cur.size();
        for (; pos < len; pos++) {
            if (cur[pos] != target[pos]) {
                break;
            }
        }

        int minSwap = len;
        for (int i = pos + 1; i < len; ++i) {
            if (cur[i] == target[pos]) {
                swap(cur[pos], cur[i]);
                minSwap = min(minSwap, 1 + dfs(cur, target));
                swap(cur[pos], cur[i]);
            }
        }
        memo[cur] = minSwap;
        return minSwap;
    }
public:
    int kSimilarity(string A, string B) {
        memo[B] = 0;
        return dfs(A, B);
    }
};

class Solution1 { // BFS
private:
    vector<string> neighbors(string S, string target) {
        vector<string> result;
        int pos = 0;
        for (; pos < S.size(); pos++) {
            if (S[pos] != target[pos]) {
                break;
            }
        }

        for (int j = pos + 1; j < S.size(); j++) {
            if (S[j] == target[pos]) {
                swap(S[j], S[pos]);
                result.push_back(S);
                swap(S[j], S[pos]);
            }
        }
        return result;
    }
public:
    int kSimilarity(string A, string B) {
        unordered_set<string> visited;
        visited.insert(A);
        queue<string> bfs;
        bfs.push(A);
        int step = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                string cur = bfs.front();
                bfs.pop();
                if (cur == B) {
                    return step;
                }

                for (string next : neighbors(cur, B)) {
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        bfs.push(next);
                    }
                }
            }
            step += 1;
        }
        return INT_MAX;
    }
};
