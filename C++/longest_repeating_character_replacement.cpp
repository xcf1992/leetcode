/*
424. Longest Repeating Character Replacement
Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times. Find the length of a longest substring containing all repeating letters you can get after performing the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
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

/*
maxCount may be invalid at some points, but this doesn't matter, 
because it was valid earlier in the string, 
and all that matters is finding the max window that occurred anywhere in the string. 
Additionally, it will expand if and only if enough repeating characters appear in the window to make it expand. 
So whenever it expands, it's a valid expansion.
*/
class Solution {
public:
    int characterReplacement(string s, int k) {
        int result = 0;
        int start = 0;
        int maxCount = 0;
        vector<int> count(26, 0);
        for (int end = 0; end < s.size(); end++) {
            count[s[end] - 'A'] += 1;
            maxCount = max(maxCount, count[s[end] - 'A']);
            if (end - start + 1 - maxCount > k) {
                count[s[start] - 'A'] -= 1;
                start += 1;
            }
            result = max(result, end - start + 1);
        }
        return result;
    }
};
