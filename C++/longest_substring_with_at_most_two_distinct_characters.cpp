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
#include <stdio.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int n = s.size();
        if (n <= 2) {
            return n;
        }

        int result = 0;
        int begin = 0;
        int end = 1;
        int distinct = 1;
        unordered_map<char, int> count;
        count[s[begin]] = 1;
        while (end < n) {
            if (count[s[end]] != 0) {
                count[s[end]] += 1;
                end += 1;
            }
            else if (distinct == 1) {
                count[s[end]] = 1;
                end += 1;
                distinct += 1;
            }
            else if (distinct == 2) {
                result = max(result, end - begin);
                while (begin < end and distinct == 2) {
                    count[s[begin]] -= 1;
                    if (count[s[begin]] == 0) {
                        distinct = 1;
                    }
                    begin += 1;
                }
            }
        }
        return max(result, end - begin);
    }
};
