/*
1371. Find the Longest Substring Containing Vowels in Even Counts
https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/

Given the string s,
return the size of the longest substring containing each vowel an even number of times.
That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

Example 1:
Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.

Example 2:
Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.

Example 3:
Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.

Constraints:
1 <= s.length <= 5 x 10^5
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
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
cur records the count of "aeiou"
cur & 1 = the records of a % 2
cur & 2 = the records of e % 2
cur & 4 = the records of i % 2
cur & 8 = the records of o % 2
cur & 16 = the records of u % 2
seen note the index of first occurrence of cur

Note that we don't really need the exact count number,
we only need to know if it's odd or even.

If it's one of aeiou,
'aeiou'.find(c) can find the index of vowel,
cur ^= 1 << 'aeiou'.find(c) will toggle the count of vowel.

But for no vowel characters,
'aeiou'.find(c) will return -1,
that's reason that we do 1 << ('aeiou'.find(c) + 1) >> 1.

Hope this explain enough.

Complexity
Time O(N), Space O(1)
*/
class Solution {
private:
    bool isVowel(char c) {
        return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u';
    }
public:
    int findTheLongestSubstring(string s) {
        unordered_map<char, int> mp = {{'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}};
        unordered_map<vector<int>, int> vis;
        vector<int> v(5, 0);
        vis[v] = -1;
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (isVowel(c)) {
                v[mp[c]] = 1 - v[mp[c]];
            }
            if (!vis.count(v)) {
                vis[v] = i;
            }
            res = max(res, i - vis[v]);
        }
        return res;
    }
};
