/*
17. Letter Combinations of a Phone Number
https://leetcode.com/problems/letter-combinations-of-a-phone-number/

Given a string containing digits from 2-9 inclusive,
return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

Example:
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
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
#include <numeric>
using namespace std;

class Solution {
private:
    vector<string> dfs(string &digits, int start, int end, unordered_map<char, string> &phone) {
        if (start > end) {
            return {};
        }

        vector<string> result;
        if (start == end) {
            for (char c: phone[digits[start]]) {
                result.push_back(string(1, c));
            }
            return result;
        }

        for (string combin: dfs(digits, start, end - 1, phone)) {
            for (char c: phone[digits[end]]) {
                combin.push_back(c);
                result.push_back(combin);
                combin.pop_back();
            }
        }
        return result;
    }

public:
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        unordered_map<char, string> phone;
        phone.insert({'2', "abc"});
        phone.insert({'3', "def"});
        phone.insert({'4', "ghi"});
        phone.insert({'5', "jkl"});
        phone.insert({'6', "mno"});
        phone.insert({'7', "pqrs"});
        phone.insert({'8', "tuv"});
        phone.insert({'9', "wxyz"});
        phone.insert({'0', " "});
        return dfs(digits, 0, n - 1, phone);
    }
};