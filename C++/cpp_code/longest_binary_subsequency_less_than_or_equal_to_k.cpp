/*
https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/
2311. Longest Binary Subsequence Less Than or Equal to K

You are given a binary string s and a positive integer k.

Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.

Note:

The subsequence can contain leading zeroes.
The empty string is considered to be equal to 0.
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.


Example 1:

Input: s = "1001010", k = 5
Output: 5
Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
The length of this subsequence is 5, so 5 is returned.
Example 2:

Input: s = "00101001", k = 1
Output: 6
Explanation: "000001" is the longest subsequence of s that makes up a binary number less than or equal to 1, as this number is equal to 1 in decimal.
The length of this subsequence is 6, so 6 is returned.


Constraints:

1 <= s.length <= 1000
s[i] is either '0' or '1'.
1 <= k <= 109
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
So, is it okay to include all the 0s?
Yes, because choosing a 0 is always better than choosing a 1.
Suppose we’ve already selected a subsequence and now want to add a 0 to it.
While the 0 itself does not increase the binary value,
it does double the contribution of any 1s already present by shifting them to higher positions.
However, if needed, we can simply remove the highest-order 1 to maintain the binary value,
keeping the total length the same. Therefore, adding a 0 is always beneficial
or at least non-harmful compared to adding a 1.
 */
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        int zeros = 0;
        int ones = 0;
        long long value = 0, pow = 1;

        for (char c : s) {
            if (c == '0') zeros++;
        }

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '1') {
                if (value + pow > k) {
                    continue; // Skip this '1' as it would exceed k
                }
                value += pow;
                ones++;
            }
            pow <<= 1;
            if (pow > k) break; // Further bits would exceed k
        }

        return zeros + ones;
    }
};