/*
https://leetcode.com/problems/number-of-ways-to-select-buildings/description/
2222. Number of Ways to Select Buildings

You are given a 0-indexed binary string s which represents the types of buildings along a street where:

s[i] = '0' denotes that the ith building is an office and
s[i] = '1' denotes that the ith building is a restaurant.
As a city official, you would like to select 3 buildings for random inspection. However, to ensure variety, no two
consecutive buildings out of the selected buildings can be of the same type.

For example, given s = "001101", we cannot select the 1st, 3rd, and 5th buildings as that would form "011" which is not
allowed due to having two consecutive buildings of the same type. Return the number of valid ways to select 3 buildings.



Example 1:

Input: s = "001101"
Output: 6
Explanation:
The following sets of indices selected are valid:
- [0,2,4] from "001101" forms "010"
- [0,3,4] from "001101" forms "010"
- [1,2,4] from "001101" forms "010"
- [1,3,4] from "001101" forms "010"
- [2,4,5] from "001101" forms "101"
- [3,4,5] from "001101" forms "101"
No other selection is valid. Thus, there are 6 total ways.
Example 2:

Input: s = "11100"
Output: 0
Explanation: It can be shown that there are no valid selections.


Constraints:

3 <= s.length <= 105
s[i] is either '0' or '1'.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    long long numberOfWays(string s) {
        int n = s.size();
        long long cnt_0_after = 0;
        long long cnt_1_after = 0;
        for (char c : s) {
            if (c == '0') {
                cnt_0_after++;
            } else {
                cnt_1_after++;
            }
        }

        long long cnt_0_pre = 0;
        long long cnt_1_pre = 0;
        long long rst = 0;
        for (char c : s) {
            if (c == '0') {
                rst += cnt_1_pre * cnt_1_after;
                cnt_0_pre += 1;
                cnt_0_after -= 1;
            } else {
                rst += cnt_0_pre * cnt_0_after;
                cnt_1_after -= 1;
                cnt_1_pre += 1;
            }
        }
        return rst;
    }
};