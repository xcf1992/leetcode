/*
159. Longest Substring with At Most Two Distinct Characters

Given a string s, find the length of the longest substring t that contains at most 2 distinct characters.

Example 1:
Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.

Example 2:
Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.
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
#include <map>
#include <climits>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> pos;
        int start = 0;
        int end = 0;
        int count = 0;
        int result = 0;
        while (end < s.size()) {
            if (pos.find(s[end]) == pos.end() or pos[s[end]] < start) {
                count += 1;
            }
            pos[s[end]] = end;

            while (count > 2) {
                if (start == pos[s[start]]) {
                    count -= 1;
                }
                start += 1;
            }
            result = max(result, end - start + 1);
            end += 1;
        }
        return result;
    }
};
