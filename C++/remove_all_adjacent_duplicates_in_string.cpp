/*
 1047. Remove All Adjacent Duplicates In String

 Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

 We repeatedly make duplicate removals on S until we no longer can.

 Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.



 Example 1:

 Input: "abbaca"
 Output: "ca"
 Explanation:
 For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".


 Note:

 1 <= S.length <= 20000
 S consists only of English lowercase letters.

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
public:
    string removeDuplicates(string S) {
        int n = S.size();
        if (n <= 1) {
            return S;
        }

        string result = "";
        result.push_back(S[0]);
        for (int pos = 1; pos < n; ++pos) {
            if (!result.empty() and result.back() == S[pos]) {
                result.pop_back();
            }
            else {
                result.push_back(S[pos]);
            }
        }
        return result;
    }
};
