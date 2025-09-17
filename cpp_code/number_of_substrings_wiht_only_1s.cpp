/*
1513. Number of Substrings With Only 1s
https://leetcode.com/problems/number-of-substrings-with-only-1s/

Given a binary string s (a string consisting only of '0' and '1's).
Return the number of substrings with all characters 1's.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.

Example 2:
Input: s = "101"
Output: 2
Explanation: Substring "1" is shown 2 times in s.

Example 3:
Input: s = "111111"
Output: 21
Explanation: Each substring contains only 1's characters.

Example 4:
Input: s = "000"
Output: 0

Constraints:
s[i] == '0' or s[i] == '1'
1 <= s.length <= 10^5
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
/*
    int numSub(string s) {
        int res = 0, count = 0, mod = 1e9 + 7;
        for (char c: s) {
            count = c == '1' ? count + 1 : 0;
            res = (res + count) % mod;
        }
        return res;
    }
*/
class Solution {
public:
    int numSub(string s) {
        long long result = 0;
        int left = 0;
        int right = 0;
        int n = s.size();
        int mod = 1e9 + 7;
        while (left < n) {
            while (left < n and s[left] == '0') {
                left += 1;
            }

            right = left;
            while (right < n and s[right] == '1') {
                right += 1;
            }

            long long count = right - left;
            long long number = (count * (count + 1) / 2) % mod;
            result = (number + result) % mod;
            left = right;
        }
        return result;
    }
};
