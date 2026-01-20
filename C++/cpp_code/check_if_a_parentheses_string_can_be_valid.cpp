/*
https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/
2116. Check if a Parentheses String Can Be Valid

A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following
conditions is true:

It is ().
It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
It can be written as (A), where A is a valid parentheses string.
You are given a parentheses string s and a string locked, both of length n. locked is a binary string consisting only of
'0's and '1's. For each index i of locked,

If locked[i] is '1', you cannot change s[i].
But if locked[i] is '0', you can change s[i] to either '(' or ')'.
Return true if you can make s a valid parentheses string. Otherwise, return false.



Example 1:


Input: s = "))()))", locked = "010100"
Output: true
Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.
Example 2:

Input: s = "()()", locked = "0000"
Output: true
Explanation: We do not need to make any changes because s is already valid.
Example 3:

Input: s = ")", locked = "0"
Output: false
Explanation: locked permits us to change s[0].
Changing s[0] to either '(' or ')' will not make s valid.
Example 4:

Input: s = "(((())(((())", locked = "111111010111"
Output: true
Explanation: locked permits us to change s[6] and s[8].
We change s[6] and s[8] to ')' to make s valid.


Constraints:

n == s.length == locked.length
1 <= n <= 105
s[i] is either '(' or ')'.
locked[i] is either '0' or '1'.
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.size();
        if (n & 1) {
            return false;
        }

        stack<int> open_idx;
        stack<int> unlocked_idx;
        for (int i = 0; i < n; i++) {
            if (locked[i] == '0') {
                unlocked_idx.push(i);
            } else if (s[i] == '(') {
                open_idx.push(i);
            } else if (s[i] == ')') {
                if (!open_idx.empty()) {
                    open_idx.pop();
                } else if (!unlocked_idx.empty()) {
                    unlocked_idx.pop();
                } else {
                    return false;
                }
            }
        }

        while (!open_idx.empty() && !unlocked_idx.empty() && open_idx.top() < unlocked_idx.top()) {
            open_idx.pop();
            unlocked_idx.pop();
        }

        if (open_idx.empty() && !unlocked_idx.empty()) {
            return unlocked_idx.size() % 2 == 0;
        }
        return open_idx.empty();
    }
};