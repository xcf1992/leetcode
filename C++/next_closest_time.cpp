/*
681. Next Closest Time
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits.
There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.
It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22.
It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
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
    string nextClosestTime(string time) {
        vector<char> digits;
        for (char c : time) {
            if (c != ':') {
                digits.push_back(c);
            }
        }
        sort(digits.begin(), digits.end());

        for (int i = 0; i < 4; i++) {
            if (digits[i] > time[4]) {
                time[4] = digits[i];
                return time;
            }
        }
        time[4] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (digits[i] > '5') {
                break;
            }
            if (digits[i] > time[3]) {
                time[3] = digits[i];
                return time;
            }
        }
        time[3] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (time[0] == '2' and digits[i] > '3') {
                break;
            }
            if (digits[i] > time[1]) {
                time[1] = digits[i];
                return time;
            }
        }
        time[1] = digits[0];

        for (int i = 0; i < 4; i++) {
            if (digits[i] > '2') {
                break;
            }
            if (digits[i] > time[0]) {
                time[0] = digits[i];
                return time;
            }
        }
        time[0] = digits[0];
        return time;
    }
};
