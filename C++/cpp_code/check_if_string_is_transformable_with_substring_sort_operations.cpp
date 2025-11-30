/*
1585. Check If String Is Transformable With Substring Sort Operations
https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/

Given two strings s and t,
you want to transform string s into string t using the following operation any number of times:

Choose a non-empty substring in s and sort it in-place so the characters are in ascending order.
For example, applying the operation on the underlined substring in "14234" results in "12344".

Return true if it is possible to transform string s into string t. Otherwise, return false.
A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "84532", t = "34852"
Output: true
Explanation: You can transform s into t using the following sort operations:
"84532" (from index 2 to 3) -> "84352"
"84352" (from index 0 to 2) -> "34852"

Example 2:
Input: s = "34521", t = "23415"
Output: true
Explanation: You can transform s into t using the following sort operations:
"34521" -> "23451"
"23451" -> "23415"

Example 3:
Input: s = "12345", t = "12435"
Output: false

Example 4:
Input: s = "1", t = "2"
Output: false

Constraints:
s.length == t.length
1 <= s.length <= 105
s and t only contain digits from '0' to '9'.
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
If ch[i] > ch[j], we can swap these characters. In other words, we can move a character freely to the left, until it
hits a smaller character, e.g.:

"0231" > "0213" > "0123"

So, we do not need to sort anything, we just need to check if we can move required characters to the left to get the
target string.

Note: we can also process the string right-to-left and move larger numbers right. In that case, we can just pop used
indexes instead tracking them in a separate array pos. I though about it, but it appeared a bit harder to get right
during the contest. If interested, check the solution by 0xFFFFFFFF in the comments below.

Algorithm
Collect indexes of all characters 0-9 of the source strings in idx. For each characters, we track which indexes we have
used in pos.

For each character ch in the target string, check if we have it in idx. If so, verify that there are no smaller
characters in front of it. To do that, we check the current idexes of all characters less than ch.

If the character can be moved, mark its index as used by advancing pos[ch].
*/
class Solution {
public:
    bool isTransformable(string s, string t) {
        vector<vector<int>> idx(10);
        for (int i = 0; i < s.size(); ++i) {
            idx[s[i] - '0'].push_back(i);
        }

        vector<int> pos(10, 0);
        for (auto ch : t) {
            int cur = ch - '0';
            if (pos[cur] >= idx[cur].size()) {
                return false;
            }

            for (auto i = 0; i < cur; ++i) {
                if (pos[i] < idx[i].size() and idx[i][pos[i]] < idx[cur][pos[cur]]) {
                    return false;
                }
            }
            pos[cur] += 1;
        }
        return true;
    }
};