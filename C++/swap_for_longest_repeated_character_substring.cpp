/*
1156. Swap For Longest Repeated Character Substring

Given a string text,
we are allowed to swap two of the characters in the string.
Find the length of the longest substring with repeated characters.

Example 1:
Input: text = "ababa"
Output: 3
Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa", which its length is 3.

Example 2:
Input: text = "aaabaaa"
Output: 6
Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa", which its length is 6.

Example 3:
Input: text = "aaabbaaa"
Output: 4

Example 4:
Input: text = "aaaaa"
Output: 5
Explanation: No need to swap, longest repeated character substring is "aaaaa", length is 5.

Example 5:
Input: text = "abcdef"
Output: 1

Constraints:
1 <= text.length <= 20000
text consist of lowercase English characters only.
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
using namespace std;

class Solution {
public:
    int maxRepOpt1(string text) {
        vector<vector<int>> index(26);
        for (int i = 0; i < text.size(); ++i) {
            index[text[i] - 'a'].push_back(i);
        }

        int result = 0;
        for (int i = 0; i < 26; ++i) if (!index[i].empty()) {
            int count1 = 1;
            int count2 = 0;
            int len = 0;
            for (int j = 1; j < index[i].size(); ++j) {
                if (index[i][j] == 1 + index[i][j - 1]) {
                    count1 += 1;
                }
                else {
                    count2 = index[i][j] == 2 + index[i][j - 1] ? count1 : 0;
                    count1 = 1;
                }
                len = max(len, count1 + count2);
            }
            /*
            * In the end, we'll get a max count of the repeated characters with no more than one-character gap.
            * If we have more of that character somewhere in the string (idx[n].size() > len),
            * we add 1 for the swap operation.
            */
            result = max(result, len + (index[i].size() > len ? 1 : 0));
        }
        return result;
    }
};
