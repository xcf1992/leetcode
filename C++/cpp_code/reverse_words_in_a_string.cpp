/*
151. Reverse Words in a String
https://leetcode.com/problems/reverse-words-in-a-string/

Given an input string, reverse the string word by word.

Example 1:
Input: "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

Note:
A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces.
However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.
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
    string reverseWords(string s) {
        int n = s.size();
        if (n <= 0) {
            return s;
        }

        string result = "";
        int right = n - 1;
        while (right >= 0) {
            if (right >= 0 and s[right] == ' ') {
                right -= 1;
                continue;
            }

            int left = right;
            while (left - 1 >= 0 and s[left - 1] != ' ') {
                left -= 1;
            }

            string word = s.substr(left, right - left + 1);
            if (result.empty()) {
                result += word;
            } else {
                result += " " + word;
            }

            right = left - 1;
        }
        return result;
    }
};