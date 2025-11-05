/*
679. 24 Game
You have 4 cards each containing a number from 1 to 9.
You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

Example 1:
Input: [4, 1, 8, 7]
Output: True
Explanation: (8-4) * (7-1) = 24
Example 2:
Input: [1, 2, 1, 2]
Output: False

Note:
The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
Every operation done is between two numbers.
In particular, we cannot use - as a unary operator.
For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
You cannot concatenate numbers together.
For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.
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
    bool judgePoint24(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        do {
            if (valid(nums)) {
                return true;
            }
        } while (next_permutation(nums.begin(), nums.end()));
        return false;
    }

private:
    bool valid(vector<int> &nums) {
        double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        if (valid(a + b, c, d) or valid(a - b, c, d) or valid(a * b, c, d) or valid(a / b, c, d)
        )
        {
            return true;
        }
        if (valid(a, b + c, d) or valid(a, b - c, d) or valid(a, b * c, d) or valid(a, b / c, d)
        )
        {
            return true;
        }
        if (valid(a, b, c + d) or valid(a, b, c - d) or valid(a, b, c * d) or valid(a, b, c / d)
        )
        {
            return true;
        }
        return false;
    }

    bool valid(double a, double b, double c) {
        if (valid(a + b, c) or valid(a - b, c) or valid(a * b, c) or(b != 0 and valid(a / b, c))
        )
        {
            return true;
        }
        if (valid(a, b + c) or valid(a, b - c) or valid(a, b * c) or(c != 0 and valid(a, b / c))
        )
        {
            return true;
        }
        return false;
    }

    bool valid(double a, double b) {
        if (abs(a + b - 24.0) < 0.0001 or abs(a - b - 24.0)
        <
        0.0001
        or abs(a * b - 24.0)
        <
        0.0001
        or(b != 0 and abs(a / b - 24.0) < 0.0001)
        )
        {
            return true;
        }
        return false;
    }
};