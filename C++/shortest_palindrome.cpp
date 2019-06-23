/*
214. Shortest Palindrome
Given a string s,
you are allowed to convert it to a palindrome by adding characters in front of it.
Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
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
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {

    }
};

// memory limit exceed
class Solution1 {
public:
    string shortestPalindrome(string s) {
        string s2 = s;
        reverse(s2.begin(), s2.end());
        int n = s.size();
        for (int l = n; l >= 0; l--){
            if (s.substr(0, l) == s2.substr(n - l))
                return s2.substr(0, n - l) + s;
        }
        return s;
    }
};
