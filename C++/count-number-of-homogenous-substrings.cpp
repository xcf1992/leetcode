/*
1759. Count Number of Homogenous Substrings
https://leetcode.com/problems/count-number-of-homogenous-substrings/

Given a string s, return the number of homogenous substrings of s.
Since the answer may be too large, return it modulo 109 + 7.

A string is homogenous if all the characters of the string are the same.
A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
Example 2:
Input: s = "xy"
Output: 2
Explanation: The homogenous substrings are "x" and "y".
Example 3:
Input: s = "zzzzz"
Output: 15

Constraints:
1 <= s.length <= 105
s consists of lowercase letters.
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
#include <bitset>
using namespace std;

class Solution {
public:
    int countHomogenous(string s) {
        int res = 0, cur = 0, count = 0, mod = 1e9 + 7;
        for (int a: s) {
            count = a == cur ? count + 1 : 1;
            cur = a;
            res = (res + count) % mod;
        }
        return res;
    }
};
