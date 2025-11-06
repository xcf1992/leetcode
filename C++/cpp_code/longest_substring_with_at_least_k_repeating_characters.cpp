/*
395. Longest Substring with At Least K Repeating Characters
https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/

Find the length of the longest substring T of a given string
(consists of lowercase letters only)
such that every character in T appears no less than k times.

Example 1:
Input:
s = "aaabb", k = 3
Output:
3
The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:
Input:
s = "ababbc", k = 2
Output:
5
The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
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
in the first pass I record counts of every character in a hashmap
in the second pass I locate the first character that appear less than k times in the string.
this character is definitely not included in the result, and that separates the string into two parts.
keep doing this recursively and the maximum of the left/right part is the answer.

====

This can be further optimized.
When we recurse on the string, we partition and act on the first partition itself!.

that is
rec = max(rec(f(substring_after_first_invalid)), rec(string_before_first_invalid))

Instead, we can do this
rec = max(rec(substring_before_first_invalid),
          rec(substring_from_first_invalid_to_secnd_invalid),
          rec(substring_from_second_to_third), ...
          rec(substr(n - 1 _ to _ n)))

=====================
In every step of DC,
at least 1 character,
let's say, 'a',
\is chosen to divide the string,
then all substrings in following recursive calls have no 'a'.
The level of DC is at most 26,
otherwise you run out of character to divide,
and each level is O(n). The run time is 3 ms.
*/
class Solution {
private:
    int find(string s, int k, int start, int end) {
        if (start > end) {
            return 0;
        }

        vector<int> count(26, 0);
        for (int i = start; i <= end; i++) {
            count[s[i] - 'a'] += 1;
        }

        int pos = start;
        while (pos <= end and count[s[pos] - 'a'] >= k) {
            pos += 1;
        }
        if (pos > end) {
            return end - start + 1;
        }

        int result = 0;
        int left = start;
        for (int i = start; i <= end; ++i) {
            if (count[s[i] - 'a'] < k) {
                result = max(result, find(s, k, left, i - 1));
                left = i + 1;
            }
        }
        return max(result, find(s, k, left, end));
    }

public:
    int longestSubstring(string s, int k) {
        return find(s, k, 0, s.size() - 1);
    }
};
