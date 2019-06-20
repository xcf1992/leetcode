/*
340. Longest Substring with At Most K Distinct Characters
Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.
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

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> pos;
        int start = 0;
        int end = 0;
        int count = 0;
        int result = 0;
        while (end < s.size()) {
            if (pos.find(s[end]) == pos.end() || pos[s[end]] < start) {
                count += 1;
            }
            pos[s[end]] = end;

            while (count > k) {
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
