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

/*
rolling hash
take s = "abaa" for example
as we mentioned in solution1, s2 = "aaba"
we want to find the longest prefix of s1 == suffix of s2
so we keep calculating hash value hash1 and hash2
let's say in the final result, the longest length is n
as s starts from 0, so the first character will be the one with val(s[0]) * B^(n - 1)
while s2's suffix end with last character, which is also the first character of s
so the value is val(s[0]) * B^(0), while we will keep increasing POW value.
*/
class Solution {
private:
    long B = 29;
    long MOD = 1e9 + 7;
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        int pos = -1;
        long hash1 = 0;
        long hash2 = 0;
        long POW = 1;
        for (int i = 0; i < n; ++i) {
            int val = s[i] - 'a' + 1;
            hash1 = (hash1 * B + val) % MOD;
            hash2 = (hash2 + val * POW) % MOD;
            if (hash1 == hash2) {
                pos = i;
            }
            POW = POW * B % MOD;
        }
        string s2 = s.substr(pos + 1);
        reverse(s2.begin(), s2.end());
        return s2 + s;
    }
};

/*
memory limit exceed
we try to check the if prefix of s == suffic of s2 (reverse of s)
if we find one, then we construc the result with the prefix of s2 + s
cause the suffix of s2 will be the same as prefix of s
*/
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
