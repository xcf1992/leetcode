/*
424. Longest Repeating Character Replacement
https://leetcode.com/problems/longest-repeating-character-replacement/

Given a string that consists of only uppercase English letters,
you can replace any letter in the string with another letter at most k times.
Find the length of a longest substring containing all repeating letters you can get after performing the above
operations.

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

=====
Example:
For a window "xxxyz",
end-start+1-maxCount would equal 2.
(maxCount is 3 and there are 2 characters here, "y" and "z" that are not "x" in the window.)

We are allowed to have at most k replacements in the window,
so when end-start+1-maxCount > k,
then there are more characters in the window than we can replace,
and we need to shrink the window.

If we have window with "xxxy" and k = 1,
that's fine because end-start+1-maxCount = 1, which is not > k.
maxLength gets updated to 4.

But if we then find a "z" after, like "xxxyz",
then we need to shrink the window because now end-start+1-maxCount = 2, and 2 > 1.
The window becomes "xxyz".

as we only care about the max count of a letter in a window,
within k swap if we can find m occurance of letter x, then current longest result will be m + k
we only need to update the result if can find a letter repeat more than m times within k swap
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
It became invalid. But at this time, do we have to shrink the window?
——No, we shift the whole window rightwards by one unit. So that the length is unchanged.
The reason for that is , any index smaller than original "start",
will never have the chance to lead a longer valid substring than current length of our window.
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