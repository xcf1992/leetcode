/*
1392. Longest Happy Prefix
https://leetcode.com/problems/longest-happy-prefix/

A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
Given a string s. Return the longest happy prefix of s .
Return an empty string if no such prefix exists.

Example 1:
Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The
largest prefix which is also suffix is given by "l".

Example 2:
Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.

Example 3:
Input: s = "leetcodeleet"
Output: "leet"

Example 4:
Input: s = "a"
Output: ""

Constraints:
1 <= s.length <= 10^5
s contains only lowercase English letters.
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
#include <climits>
#include <map>
using namespace std;
/*
rolling hash
Imgaine that we are given integer array including only 0-9,
A = [1,2,3,4,5,1,2,3],
find the longest matched prefix and suffix.

For one digits, we have 1 and 3.
For two digits. we have 12 and 23
For three digits, we have 123 and 123, matched!


Explanation
Calculate the value of prefix and suffix at the same time.
Though here we have 0-25 instead of just 0-9,
so we should apply >= 26-nary instead of 10-nary.

If you're worried about the collisions,
we can easily check if prefix is equal to the suffix.
We'd better do that, like in an interview.
I didn't do that, because I knew LeetCode test cases are far from strong.

Approach 1: Incremental Hash
Compute hashes for increasing prefix and suffix, reusing the previously computed hashes. This is similar to the
Karp–Rabin algorithm.

For the string of i size, the hash is: s[0] * 26 ^ (i - 1) + s[1] * 26 ^ (i -2) + ... + s[i - 2] * 26 + s[i - 1].

For the prefix hash, we will multiply the previous value by 26 and add a new letter.
For the suffix hash, we add a new letter multiplied by 26 ^ (i - 1).
Note that we need to use some large prime as a modulo to avoid overflow errors, e.g. 10 ^ 9 + 7.

Beware of collisions. After you find a matching hash, you need to check the string. Since OJ test cases do not cause
collisions, I am not doing it here.

Update: see sample solutions that handle collisions in the appendices bellow.

Example strings with collisions:

"vwantmbocxcwrqtvgzuvgrmdltfiglltaxkjfajxthcppcatddcunpkqsgpnjjgqanrwabgrtwuqbrfl"
"gqijndnbohkujykncuooajkhsxcbjbwhrrfgkliqatdndcrpmaqa"
"tzqzalgnxstxzlul"
*/
class Solution {
public:
    string longestPrefix(string& s) {
        long h1 = 0, h2 = 0, mul = 1, len = 0, mod = 1000000007;
        for (int i = 0, j = s.length() - 1; j > 0; ++i, --j) {
            int first = s[i] - 'a';
            int last = s[j] - 'a';
            h1 = (h1 * 26 + first) % mod;
            h2 = (h2 + mul * last) % mod;
            mul = mul * 26 % mod;
            if (h1 == h2) {
                len = i + 1;
            }
        }
        return s.substr(0, len);
    }
};