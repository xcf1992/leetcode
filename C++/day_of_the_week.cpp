/*
1185. Day of the Week
https://leetcode.com/problems/day-of-the-week/

Given a date, return the corresponding day of the week for that date.

The input is given as three integers representing the day, month and year respectively.

Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.



Example 1:

Input: day = 31, month = 8, year = 2019
Output: "Saturday"
Example 2:

Input: day = 18, month = 7, year = 1999
Output: "Sunday"
Example 3:

Input: day = 15, month = 8, year = 1993
Output: "Sunday"


Constraints:

The given dates are valid dates between the years 1971 and 2100.
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
#include <set>
#include "extra_data_types.hpp"
using namespace std;

// we can still solve this problem based on 1971-1-1 is Friday.
class Solution {
private:
    vector<string> week = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
public:
    string dayOfTheWeek(int day, int month, int year) {
        int num = 0;
        for (int i = 1971; i < year; ++i) {
            num += 365;
            if (i % 4 == 0 and (i % 100 != 0 or i % 400 == 0)) {
                num += 1;
            }
        }

        if (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)) {
            days[1] = 29;
        }

        for (int i = 1; i < month; ++i) {
            num += days[i - 1];
        }
        num += day - 1;
        return week[(num + 5) % 7];
    }
};
