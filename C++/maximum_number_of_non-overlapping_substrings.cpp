/*
1520. Maximum Number of Non-Overlapping Substrings
https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/

Given a string s of lowercase letters,
you need to find the maximum number of non-empty substrings of s that meet the following conditions:

The substrings do not overlap, that is for any two substrings s[i..j] and s[k..l],
either j < k or i > l is true.
A substring that contains a certain character c must also contain all occurrences of c.
Find the maximum number of substrings that meet the above conditions.
If there are multiple solutions with the same number of substrings,
return the one with minimum total length.
It can be shown that there exists a unique solution of minimum total length.

Notice that you can return the substrings in any order.

Example 1:
Input: s = "adefaddaccc"
Output: ["e","f","ccc"]
Explanation: The following are all the possible substrings that meet the conditions:
[
  "adefaddaccc"
  "adefadda",
  "ef",
  "e",
  "f",
  "ccc",
]
If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.

Example 2:
Input: s = "abbaccd"
Output: ["d","bb","cc"]
Explanation: Notice that while the set of substrings ["d","abba","cc"] also has length 3, it's considered incorrect since it has larger total length.

Constraints:
1 <= s.length <= 10^5
s contains only lowercase English letters.
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
https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/discuss/743223/C%2B%2B-Greedy-O(n)
Oh, human, so many edge cases... Update: see below for FAQ.

The greedy logic is quite simple though:

If we find a valid substring, and then another valid substring within the first substring - we can ignore the larger substring.
E.g. if we find "abccba", and then "bccb", and then "cc", we only care about "cc". This can be easily proven by a contradition.
First, collect left (l) and right(r) indices for every character.
Then, go through the string. If the current index i is the left index for the character s[i], it may be a valid substring.
We then use a sliding window pattern to find the lendth of the substring.
If we find a character that appears before i - we do not have a valid string starting at i.
If substring is valid, we remember it, as well as it's right edge.
This logic, repeated, will ensure that we find the valid substring with the smallest right edge.
If the valid substring starts after the previous right edge, there is no overlap. The previous substring should be included into the result.
FAQ

Why the answer for "abab" is "abab", and not "bab"?
According to condition 2 (see the problem description): a substring containing 'a' must also contain all occurrences of 'a'. So, "bab" is simply not a valid substring. This is checked by this line in the code below: if (l[s[j] - 'a'] < i).
The time complexity seems to be O(n ^ 2). There are two nested loops, each goes through n elements in the worst case.
Correct, the inner loop could go through n elements, but we will do it no more than 26 times. We only search for a substring starting form indexes in l, and we have 26 such indexes. This is checked by this line: if (i == l[s[i] - 'a']).
Alternatively, instead of going through n elements in the outer loop, we can just go iterate through indexes in l directly. However, we need to sort l in that case, which complicates the implementation a bit. Some folks suggested to use a stack, but the implementation was just longer :)
Why do we need to do res.push_back("")?
OK, so we have a buch on edge condition, and I was shooting for the simplest code. Instead, we can have a string variable, and push that variable to the result. However, that will require another check in the end to make sure the latest string is included.
*/
class Solution {
private:
    int checkSubstr(string &s, int i, vector<int> &l, vector<int> &r) {
        int right = r[s[i] - 'a'];
        for (auto j = i; j <= right; ++j) {
            if (l[s[j] - 'a'] < i)
                return -1;
            right = max(right, r[s[j] - 'a']);
        }
        return right;
    }
public:
    vector<string> maxNumOfSubstrings(string s) {
        vector<int> l(26, INT_MAX), r(26, INT_MIN);
        vector<string> res(1);
        for (auto i = 0; i < s.size(); ++i) {
            l[s[i] - 'a'] = min(l[s[i] - 'a'], i);
            r[s[i] - 'a'] = max(r[s[i] - 'a'], i);
        }
        
        auto right = INT_MAX;
        for (auto i = 0; i < s.size(); ++i) {
            if (i == l[s[i] - 'a']) {
                auto new_right = checkSubstr(s, i, l, r);
                if (new_right != -1) {
                    if (i > right)
                        res.push_back("");
                    right = new_right;
                    res.back() = s.substr(i, right - i + 1);
                }
            }
        }
        return res;
    }
};
