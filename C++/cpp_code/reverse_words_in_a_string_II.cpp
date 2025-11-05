/*
186. Reverse Words in a String II
https://leetcode.com/problems/reverse-words-in-a-string-ii/

Given an input string,
reverse the string word by word.

Example:
Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]

Note:
A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces.
The words are always separated by a single space.
Follow up: Could you do it in-place without allocating extra space?
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
private:
    void flip(vector<char> &str, int start, int end) {
        while (start < end) {
            swap(str[start], str[end]);
            start += 1;
            end -= 1;
        }
    }

public:
    void reverseWords(vector<char> &str) {
        int n = str.size();
        if (n <= 1) {
            return;
        }

        flip(str, 0, n - 1);
        int start = 0;
        int end = 0;
        while (start < n) {
            while (end < n and str[end]
            !=
            ' '
            )
            {
                end += 1;
            }
            flip(str, start, end - 1);
            start = end + 1;
            end = start;
        }
    }
};