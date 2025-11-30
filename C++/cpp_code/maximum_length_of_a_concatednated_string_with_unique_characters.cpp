/*
1239. Maximum Length of a Concatenated String with Unique Characters
https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

Given an array of strings arr.
String s is a concatenation of a sub-sequence of arr which have unique characters.
Return the maximum possible length of s.

Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
Maximum length is 4.

Example 2:
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible solutions are "chaers" and "acters".

Example 3:
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26

Constraints:
1 <= arr.length <= 16
1 <= arr[i].length <= 26
arr[i] contains only lower case English letters.
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
Itearte the the input strings,
but skip the word that have duplicate characters.
The examples is kind of misleading,
but the input string can have duplicate characters,
no need to considerate these strings.
*/
class Solution {
private:
    bitset<26> getMask(string& str) {
        bitset<26> mask;
        for (char c : str) {
            mask.set(c - 'a');
        }
        return mask;
    }

public:
    int maxLength(vector<string>& arr) {
        vector<bitset<26>> dp = {bitset<26>()};
        int result = 0;
        for (string& str : arr) {
            bitset<26> mask = getMask(str);
            if (mask.count() != str.size()) {
                continue;
            }

            for (int i = dp.size() - 1; i >= 0; --i) {
                bitset<26> cur = dp[i];
                if ((cur & mask).any()) {
                    continue;
                }

                dp.push_back(cur | mask);
                result = max(result, (int)cur.count() + (int)mask.count());
            }
        }
        return result;
    }
};
