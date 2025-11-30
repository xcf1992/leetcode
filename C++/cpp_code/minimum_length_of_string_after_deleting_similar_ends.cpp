/*
1750. Minimum Length of String After Deleting Similar Ends
https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/

Given a string s consisting only of characters 'a', 'b', and 'c'.
You are asked to apply the following algorithm on the string any number of times:

Pick a non-empty prefix from the string s where all the characters in the prefix are equal.
Pick a non-empty suffix from the string s where all the characters in this suffix are equal.
The prefix and the suffix should not intersect at any index.
The characters from the prefix and suffix must be the same.
Delete both the prefix and the suffix.
Return the minimum length of s after performing the above operation any number of times (possibly zero times).

Example 1:
Input: s = "ca"
Output: 2
Explanation: You can't remove any characters, so the string stays as is.
Example 2:
Input: s = "cabaabac"
Output: 0
Explanation: An optimal sequence of operations is:
- Take prefix = "c" and suffix = "c" and remove them, s = "abaaba".
- Take prefix = "a" and suffix = "a" and remove them, s = "baab".
- Take prefix = "b" and suffix = "b" and remove them, s = "aa".
- Take prefix = "a" and suffix = "a" and remove them, s = "".
Example 3:
Input: s = "aabccabba"
Output: 3
Explanation: An optimal sequence of operations is:
- Take prefix = "aa" and suffix = "a" and remove them, s = "bccabb".
- Take prefix = "b" and suffix = "bb" and remove them, s = "cca".

Constraints:
1 <= s.length <= 105
s only consists of characters 'a', 'b', and 'c'.
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
#include <climits>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();
        if (n <= 1) {
            return n;
        }

        int left = 0;
        int right = n - 1;
        while (left < right && s[left] == s[right]) {
            int l = left;
            while (l < right && s[l + 1] == s[left]) {
                l += 1;
            }

            int r = right;
            while (r > left && s[r - 1] == s[right]) {
                r -= 1;
            }

            left = l + 1;
            right = r - 1;
        }

        if (right < left) {
            return 0;
        }
        return right - left + 1;
    }
};
