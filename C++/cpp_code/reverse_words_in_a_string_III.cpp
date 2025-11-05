/*
557. Reverse Words in a String III
https://leetcode.com/problems/reverse-words-in-a-string-iii/

Given a string,
you need to reverse the order of characters in each word within a sentence
while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Note:
In the string, each word is separated by single space and there will not be any extra space in the string.
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
    void reverse(string &word, int begin, int end) {
        while (begin < end) {
            swap(word[begin], word[end]);
            begin++;
            end--;
        }
    }

public:
    string reverseWords(string s) {
        int n = s.size();
        if (n <= 0) {
            return s;
        }

        int start = 0;
        int end = 0;
        while (end <= n) {
            if (end == n or s[end]
            ==
            ' '
            )
            {
                reverse(s, start, end - 1);
                start = end + 1;
            }
            end += 1;
        }
        return s;
    }
};