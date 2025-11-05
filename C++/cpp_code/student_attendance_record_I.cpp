/*
551. Student Attendance Record I

You are given a string representing an attendance record for a student.
The record only contains the following three characters:
'A' : Absent.
'L' : Late.
'P' : Present.

A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent)
or more than two continuous 'L' (late).
You need to return whether the student could be rewarded according to his attendance record.

Example 1:
Input: "PPALLP"
Output: True

Example 2:
Input: "PPALLL"
Output: False
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
    bool checkRecord(string s) {
        int absent = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == 'P') {
                continue;
            }
            if (c == 'A' and++
            absent > 1
            )
            {
                return false;
            }
            // we need to add s[i] == L here cause it may happen cur is A and absent < 1
            if (i > 1 and s[i]
            ==
            'L'
            and s[i - 1]
            ==
            'L'
            and s[i - 2]
            ==
            'L'
            )
            {
                return false;
            }
        }
        return true;
    }
};