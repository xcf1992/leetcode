/*
504. Base 7
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].
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
#include <climits>
using namespace std;

class Solution {
public:
    string convertToBase7(int num) {
        bool negative = false;
        if (num < 0) {
            negative = true;
            num = 0 - num;
        }

        string result = "";
        do {
            // use do-while in case num == 0
            result.push_back(num % 7 + '0');
            num = num / 7;
        } while (num > 0);
        reverse(result.begin(), result.end());
        return negative ? "-" + result : result;
    }
};