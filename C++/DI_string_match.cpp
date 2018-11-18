/*
 Given a string S that only contains "I" (increase) or "D" (decrease), let N = S.length.
 
 Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:
 
 If S[i] == "I", then A[i] < A[i+1]
 If S[i] == "D", then A[i] > A[i+1]
 
 
 Example 1:
 
 Input: "IDID"
 Output: [0,4,1,3,2]
 Example 2:
 
 Input: "III"
 Output: [0,1,2,3]
 Example 3:
 
 Input: "DDI"
 Output: [3,2,0,1]
 
 
 Note:
 
 1 <= S.length <= 1000
 S only contains characters "I" or "D".
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
    vector<int> construct(string S, int start, int end) {
        if (S.empty()) {
            return {start};
        }
        if (S == "I") {
            return {start, end};
        }
        if (S == "D") {
            return {end, start};
        }
        
        int mid = S.size() / 2;
        string leftStr = S.substr(0, mid);
        if (S[mid] == 'I') {
            vector<int> left = construct(leftStr, start, start + leftStr.size());
            if (mid == S.size() - 1) {
                left.push_back(end);
                return left;
            }
            string rightStr = S.substr(mid + 1);
            vector<int> right = construct(rightStr, end - rightStr.size(), end);
            left.insert(left.end(), right.begin(), right.end());
            return left;
        }
        
        vector<int> left = construct(leftStr, end - leftStr.size(), end);
        if (mid == S.size() - 1) {
            left.push_back(start);
            return left;
        }
        string rightStr = S.substr(mid + 1);
        vector<int> right = construct(rightStr, start, start + rightStr.size());
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }
public:
    vector<int> diStringMatch(string S) {
        int n = S.size();
        return construct(S, 0, n);
    }
};
