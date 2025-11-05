/*
1556. Thousand Separator
https://leetcode.com/problems/thousand-separator/

Given an integer n, add a dot (".") as the thousands separator and return it in string format.

Example 1:
Input: n = 987
Output: "987"

Example 2:
Input: n = 1234
Output: "1.234"

Example 3:
Input: n = 123456789
Output: "123.456.789"

Example 4:
Input: n = 0
Output: "0"

Constraints:
0 <= n < 2^31
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
#include <stdio.h>
#include <map>
using namespace std;

class Solution {
public:
    string thousandSeparator(int n) {
        string result = "";
        string num = to_string(n);
        int count = 0;
        for (int i = num.size() - 1; i >= 0; --i) {
            result += num[i];
            count += 1;
            if (count == 3 and i
            !=
            0
            )
            {
                result += ".";
                count = 0;
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};