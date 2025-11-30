/*
1653. Minimum Deletions to Make String Balanced
https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/

You are given a string s consisting only of characters 'a' and 'b'​​​​.
You can delete any number of characters in s to make s balanced.
s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
Return the minimum number of deletions needed to make s balanced.

Example 1:
Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").

Example 2:
Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.

Constraints:
1 <= s.length <= 105
s[i] is 'a' or 'b'​​.
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
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
// Idea is to traverse from right to left
// use stack to keep track if 'b' comes before 'a' in string
// then we need to pop & need to delete that character
class Solution {
public:
    int minimumDeletions(string s) {
        stack<char> st;
        int n = s.size();
        int res = 0;
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];
            if (!st.empty() && st.top() < c) {
                res++;
                st.pop();
            } else {
                st.push(c);
            }
        }
        return res;
    }
};
