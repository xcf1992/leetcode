/*
1784. Check if Binary String Has at Most One Segment of Ones
https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/

Given a binary string s ​​​​​without leading zeros,
return true​​​ if s contains at most one contiguous segment of ones.
Otherwise, return false.

Example 1:
Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.
Example 2:
Input: s = "110"
Output: true

Constraints:
1 <= s.length <= 100
s[i]​​​​ is either '0' or '1'.
s[0] is '1'.

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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    bool checkOnesSegment(string s) {
        int oneGroup = false;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '1') {
                if (oneGroup) {
                    return false;
                }

                oneGroup = true;
                while (i < s.size() && s[i] == '1') {
                    i += 1;
                }
            }
        }
        return true;
    }
};