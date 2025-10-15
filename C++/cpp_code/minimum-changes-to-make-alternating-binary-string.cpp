/*
1758. Minimum Changes To Make Alternating Binary String
https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/

You are given a string s consisting only of the characters '0' and '1'.
In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal.
For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Example 1:
Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.
Example 2:
Input: s = "10"
Output: 0
Explanation: s is already alternating.
Example 3:
Input: s = "1111"
Output: 2
Explanation: You need two operations to reach "0101" or "1010".

Constraints:
1 <= s.length <= 104
s[i] is either '0' or '1'.
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
    int minOperations(string s) {
        int res = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            if (s[i] - '0' != i % 2) {
                res++;
            }
        }
        return min(res, n - res);
    }
};
