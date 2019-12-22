/*
1297. Maximum Number of Occurrences of a Substring
https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/

Given a string s,
return the maximum number of ocurrences of any substring under the following rules:
The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.

Example 1:
Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 ocurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).

Example 2:
Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.

Example 3:
Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
Output: 3

Example 4:
Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
Output: 0

Constraints:
1 <= s.length <= 10^5
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s only contains lowercase English letters.
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
We also notice that we only need minSize
since if the minSize satisfies the constraints to have distinct letters <= maxLetters
any substring greater than that size would only add at max a new distinct letter.
*/
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        if (n < minSize) {
            return 0;
        }

        unordered_map<string, int> occurrence;
        vector<int> letter(26, 0);
        int count = 0;
        int left = 0;
        int result = 0;
        for (int right = 0; right < n; ++right) {
            letter[s[right] - 'a'] += 1;
            if (letter[s[right] - 'a'] == 1) {
                count += 1;
            }

            if (right - left + 1 > minSize) {
                letter[s[left] - 'a'] -= 1;
                if (letter[s[left] - 'a'] == 0) {
                    count -= 1;
                }
                left += 1;
            }

            int len = right - left + 1;
            if (len == minSize and count <= maxLetters) {
                string sub = s.substr(left, len);
                occurrence[sub] += 1;
                result = max(result, occurrence[sub]);
            }
        }
        return result;
    }
};
