/*
1593. Split a String Into the Max Number of Unique Substrings
https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/

Given a string s, return the maximum number of unique substrings that the given string can be split into.

You can split string s into any list of non-empty substrings,
where the concatenation of the substrings forms the original string.
However, you must split the substrings such that all of them are unique.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "ababccc"
Output: 5
Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc']
is not valid as you have 'a' and 'b' multiple times.

Example 2:
Input: s = "aba"
Output: 2
Explanation: One way to split maximally is ['a', 'ba'].

Example 3:
Input: s = "aa"
Output: 1
Explanation: It is impossible to split the string any further.

Constraints:
1 <= s.length <= 16
s contains only lower case English letters.
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
#include <cfloat>
#include <climits>
#include <map>
using namespace std;

class Solution {
private:
    unordered_set<string> memo;

public:
    int maxUniqueSplit(string& s, int start = 0) {
        if (start == s.size()) {
            return 0;
        }

        int result = -1;
        for (int len = 1; start + len <= s.size(); ++len) {
            auto it = memo.insert(s.substr(start, len));
            if (it.second) {
                int count = maxUniqueSplit(s, start + len);
                if (count != -1) {
                    result = max(result, 1 + count);
                }
                memo.erase(it.first);
            }
        }
        return result;
    }
};
