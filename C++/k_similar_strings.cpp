/*
 Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.
 
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

class Solution {
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
        unordered_map<string, int> memo;
        memo[A] = 0;
        
        queue<string> bfs;
        bfs.push(A);
        while (!bfs.empty()) {
            string cur = bfs.front();
            bfs.pop();
            
            if (cur == B) {
                return memo[cur];
            }
            for (string next : neighbors(cur, B)) {
                if (memo.find(next) == memo.end()) {
                    memo[next] = memo[cur] + 1;
                    bfs.push(next);
                }
            }
        }
        return INT_MAX;
    }
};
