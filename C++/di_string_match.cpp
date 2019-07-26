/*
 942. DI String Match
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
/*
 If we see say S[0] == 'I', we can always put 0 as the first element;
 similarly, if we see S[0] == 'D', we can always put N as the first element.

 Say we have a match for the rest of the string S[1], S[2], ...
 using N distinct elements. Notice it doesn't matter what the elements are,
 only that they are distinct and totally ordered.
 Then, putting 0 or N at the first character will match,
 and the rest of the elements (1, 2, ..., N or 0, 1, ..., N-1) can use the matching we have.

 Algorithm
 Keep track of the smallest and largest element we haven't placed.
 If we see an 'I', place the small element;
 otherwise place the large element.
 */
class Solution {
public:
    vector<int> diStringMatch(string S) {
        int left = 0;
        int right = S.size();
        vector<int> result;
        for (char c : S) {
            if (c == 'D') {
                result.push_back(right--);
            }
            else {
                result.push_back(left++);
            }
        }
        result.push_back(left);
        return result;
    }
};

class Solution1 {
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
