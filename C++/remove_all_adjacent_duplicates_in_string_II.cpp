/*
1209. Remove All Adjacent Duplicates in String II
https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/

Given a string s,
a k duplicate removal consists of choosing k adjacent and equal letters from s
and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.
Return the final string after all such duplicate removals have been made.
It is guaranteed that the answer is unique.

Example 1:
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.

Example 2:
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation:
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"

Example 3:
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"

Constraints:
1 <= s.length <= 10^5
2 <= k <= 10^4
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
#include <stdio.h>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        int n = s.size();
        if (n < k) {
            return s;
        }

        vector<pair<int, char>> stk;
        for (int i = 0; i < n; ++i) {
            if (stk.empty() or s[i] != stk.back().second) {
                stk.push_back({1, s[i]});
                continue;
            }

            if (++stk.back().first == k) {
                stk.pop_back();
            }
        }

        string result = "";
        for (pair<int, char>& p : stk) {
            result += string(p.first, p.second);
        }
        return result;
    }
};

class Solution1 { // 20%
private:
    bool findDuplicate(string& result, char c, int k) {
        if (result.size() < k - 1) {
            return false;
        }

        int n = result.size();
        if (result.substr(n - k + 1) == string(k - 1, c)) {
            result = result.substr(0, n - k + 1);
            return true;
        }
        return false;
    }
public:
    string removeDuplicates(string s, int k) {
        int n = s.size();
        if (n < k) {
            return s;
        }

        string result = "";
        result.push_back(s[0]);
        for (int i = 1; i < n; ++i) {
            if (!findDuplicate(result, s[i], k)) {
                result.push_back(s[i]);
            }
        }
        return result;
    }
};
