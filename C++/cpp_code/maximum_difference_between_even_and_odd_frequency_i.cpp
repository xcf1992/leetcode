/*
https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/description/
3442. Maximum Difference Between Even and Odd Frequency I

You are given a string s consisting of lowercase English letters.

Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in
the string such that:

a1 has an odd frequency in the string.
a2 has an even frequency in the string.
Return this maximum difference.



Example 1:

Input: s = "aaaaabbc"

Output: 3

Explanation:

The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
The maximum difference is 5 - 2 = 3.
Example 2:

Input: s = "abcabcab"

Output: 1

Explanation:

The character 'a' has an odd frequency of 3, and 'c' has an even frequency of 2.
The maximum difference is 3 - 2 = 1.


Constraints:

3 <= s.length <= 100
s consists only of lowercase English letters.
s contains at least one character with an odd frequency and one with an even frequency.
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
    int maxDifference(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a'] += 1;
        }

        int max_odd = 0;
        int min_even = s.size();
        for (int cnt : freq) {
            if (cnt == 0) {
                continue;
            }
            if (cnt % 2 == 0) {
                min_even = min(min_even, cnt);
            } else {
                max_odd = max(max_odd, cnt);
            }
        }
        return max_odd - min_even;
    }
};
