/*
1055. Shortest Way to Form String

From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).

Given two strings source and target,
return the minimum number of subsequences of source such that their concatenation equals target.
If the task is impossible, return -1.

Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".

Example 2:
Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.

Example 3:
Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".

Note:

Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
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
public:
    int shortestWay(string source, string target) {
        int n = source.size();
        if (n == 0) {
            return -1;
        }
        vector<vector<int>> dict(26);
        for (int i = 0; i < n; i++) {
            dict[source[i] - 'a'].push_back(i);
        }

        int result = 1;
        int pos = -1;
        for (int i = 0; i < target.size(); ++i) {
            int index = target[i] - 'a';
            if (dict[index].empty()) {
                return -1;
            }

            auto it = upper_bound(dict[index].begin(), dict[index].end(), pos);
            if (it == dict[index].end()) {
                result += 1;
                it = dict[index].begin();
            }
            pos = *it;
        }
        return result;
    }
};
