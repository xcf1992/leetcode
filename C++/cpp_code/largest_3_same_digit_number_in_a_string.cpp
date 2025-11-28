/*
https://leetcode.com/problems/largest-3-same-digit-number-in-string/description/
2264. Largest 3-Same-Digit Number in String

You are given a string num representing a large integer. An integer is good if it meets the following conditions:

It is a substring of num with length 3.
It consists of only one unique digit.
Return the maximum good integer as a string or an empty string "" if no such integer exists.

Note:

A substring is a contiguous sequence of characters within a string.
There may be leading zeroes in num or a good integer.


Example 1:

Input: num = "6777133339"
Output: "777"
Explanation: There are two distinct good integers: "777" and "333".
"777" is the largest, so we return "777".
Example 2:

Input: num = "2300019"
Output: "000"
Explanation: "000" is the only good integer.
Example 3:

Input: num = "42352338"
Output: ""
Explanation: No substring of length 3 consists of only one unique digit. Therefore, there are no good integers.


Constraints:

3 <= num.length <= 1000
num only consists of digits.
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
#include <numeric>
using namespace std;

class Solution {
public:
    string largestGoodInteger(string num) {
        string rst = "";
        int n = num.size();
        int left = 0;
        while (left < n - 2) {
            int right = left;
            while (right < n && right - left + 1 <= 3 && num[right] == num[left]) {
                right += 1;
            }

            if (right - left == 3) {
                string temp = num.substr(left, right - left);
                if (rst == "" || temp > rst) {
                    rst = temp;
                }
            }

            left = right;
        }
        return rst;
    }
};
