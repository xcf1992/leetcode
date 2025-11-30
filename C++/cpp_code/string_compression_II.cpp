/*
1531. String Compression II
https://leetcode.com/problems/string-compression-ii/

Run-length encoding is a string compression method that works by replacing consecutive identical characters
(repeated 2 or more times) with the concatenation of the character
and the number marking the count of the characters (length of the run).
For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed
string becomes "a2bc3".

Notice that in this problem, we are not adding '1' after single characters.

Given a string s and an integer k.
You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
Find the minimum length of the run-length encoded version of s after deleting at most k characters.

Example 1:
Input: s = "aaabcccd", k = 2
Output: 4
Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters
'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have
s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version
of s will be "a3c3" of length 4.

Example 2:
Input: s = "aabbaa", k = 2
Output: 2
Explanation: If we delete both 'b' characters, the resulting compressed string would be "a4" of length 2.

Example 3:
Input: s = "aaaaaaaaaaa", k = 0
Output: 3
Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11" of length 3.

Constraints:
1 <= s.length <= 100
0 <= k <= s.length
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
#include <cfloat>
#include <climits>
#include <map>
using namespace std;
/*
We say a group of the chars that coding as char+num in the final result as a "group". Each group covers some subarray in
the origin input, some chars in this group are removed, and the remained chars build the "group". For example, we remove
"bb" from subarray "abbaaa" and remained "aaaa", which build a group "a4".

The key point is that the first group of chars must cover a subrange begin from index 0. So we can check all subrange
indexed from 0 and just keep the most chars in those ranges.

For all problem like this one, which we need to build some "group", I always try to build the first group, and leaving
the rest as a subproblem and solve it by recursive.
*/
class Solution {
    const static int N = 127;

    // dp[left][k] means the minimal coding size for substring
    // s[left:] and removing at most k chars
    int dp[N][N];

    string str;
    int n;

    // get length of digit
    inline int xs(int x) {
        return x == 1 ? 0 : x < 10 ? 1 : x < 100 ? 2 : 3;
    }

    int solve(int left, int k) {
        if (k < 0)
            return N;  // invalid, return INF
        if (left >= n or n - left <= k)
            return 0;  // empty

        int& res = dp[left][k];
        if (res != -1)
            return res;
        res = N;

        int cnt[26] = {0};
        // we try to make s[left:j] (both inculded) as one group,
        // and all chars in this group should be the same.
        // so we must keep the most chars in this range and remove others
        // the range length is (j - left + 1)
        // and the number of chars we need to remove is (j - left + 1 - most)
        for (int j = left, most = 0; j < n; j++) {
            most = max(most, ++cnt[str[j] - 'a']);  // most = max(count(s[left:j])
            res = min(res, 1 + xs(most) + solve(j + 1, k - (j - left + 1 - most)));
        }
        return res;
    }

public:
    int getLengthOfOptimalCompression(string s, int k) {
        memset(dp, -1, sizeof(dp));
        str = s;
        n = s.size();
        return solve(0, k);
    }
};