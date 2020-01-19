/*
541. Reverse String II
https://leetcode.com/problems/reverse-string-ii/

Given a string and an integer k,
you need to reverse the first k characters for every 2k characters counting from the start of the string.
If there are less than k characters left, reverse all of them.
If there are less than 2k but greater than or equal to k characters,
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]
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
using namespace std;

class Solution {
private:
    void reverse(string& s, int start, int k) {
        if (start >= s.size()) {
            return;
        }

        int end = start + k - 1;
        if (s.size() - start < k) {
            end = s.size() - 1;
        }

        while (start <= end) {
            swap(s[start++], s[end--]);
        }
    }
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
            reverse(s, i, k);
        }
        return s;
    }
};
