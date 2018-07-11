/*
 Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:
 
 Any left parenthesis '(' must have a corresponding right parenthesis ')'.
 Any right parenthesis ')' must have a corresponding left parenthesis '('.
 Left parenthesis '(' must go before the corresponding right parenthesis ')'.
 '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
 An empty string is also valid.
 
 Example 1:
 Input: "()"
 Output: True
 Example 2:
 Input: "(*)"
 Output: True
 Example 3:
 Input: "(*))"
 Output: True
 Note:
 The string size will be in the range [1, 100].
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

class Solution {
public:
    bool checkValidString(string s) {
        int minLeft = 0; // tacking minimum possible number of (
        int maxLeft = 0; // tacking maximum possible number of (
        for (char c : s) {
            minLeft += c == '(' ? 1 : -1;
            maxLeft += c == ')' ? -1 : 1;
            if (maxLeft < 0) { // if the max possible ( is less than0 return false
                return false;
            }
            minLeft = max(0, minLeft); // is the min possible ( is less than 0, make it to be 0
        }
        return minLeft == 0;
    }
};

class Solution1 { // backtracking time limit exceeded
private:
    bool check(string s, int pos, int left, int right) {
        if (pos == s.size()) {
            return right == left;
        }
        
        if (s[pos] == '(') {
            return check(s, pos + 1, left + 1, right);
        }
        if (s[pos] == ')') {
            if (right == left) {
                return false;
            }
            return check(s, pos + 1, left, right + 1);
        }
        if (right == left) {
            return check(s, pos + 1, left + 1, right) || check(s, pos + 1, left, right);
        }
        return check(s, pos + 1, left + 1, right) || check(s, pos + 1, left, right + 1) || check(s, pos + 1, left, right);
    }
public:
    bool checkValidString(string s) {
        return check(s, 0, 0, 0);
    }
};
