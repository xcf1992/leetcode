/*
1256. Encode Number
https://leetcode.com/problems/encode-number/

Given a non-negative integer num,
Return its encoding string.
The encoding is done by converting the integer to a string using a secret function
that you should deduce from the following table:
   n   |    f(n)
   0   |    ""
   1   |    "0"
   2   |    "1"
   3   |    "00"
   4   |    "01"
   5   |    "10"
   6   |    "11"
   7   |    "000"

Example 1:
Input: num = 23
Output: "1000"

Example 2:
Input: num = 107
Output: "101100"

Constraints:
0 <= num <= 10^9
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    string encode(int num) {
        return num > 0 ? encode((num - 1) / 2) + "10"[num % 2] : "";
    }
};