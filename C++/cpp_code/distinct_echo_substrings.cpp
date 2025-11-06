/*
1316. Distinct Echo Substrings
https://leetcode.com/problems/distinct-echo-substrings/

Return the number of distinct non-empty substrings of text
that can be written as the concatenation of some string with itself
(i.e. it can be written as a + a where a is some string).

Example 1:
Input: text = "abcabcabc"
Output: 3
Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".

Example 2:
Input: text = "leetcodeleetcode"
Output: 2
Explanation: The 2 substrings are "ee" and "leetcodeleetcode".

Constraints:
1 <= text.length <= 2000
text has only lowercase English letters.
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
#include "extra_data_types.hpp"
using namespace std;
/*
terrible quesiton description, fuck it
https://leetcode.com/problems/distinct-echo-substrings/discuss/477094/Am-I-the-only-one-who-didn't-understand-the-description

*/
class Solution {
public:
    int distinctEchoSubstrings(string text) {
        unordered_set<string_view> res;
        const char* p = text.c_str();
        for (int i = 0; i < text.size(); ++i) {
            for (int len = 1; i + len + len <= text.size(); ++len) {
                const string_view a(p + i, len);
                const string_view b(p + i + len, len);
                if (a == b) {
                    res.insert(a);
                }
            }
        }
        return res.size();
    }
};