/*
539. Minimum Time Difference
Given a list of 24-hour clock time points in "Hour:Minutes" format,
find the minimum minutes difference between any two time points in the list.
Example 1:
Input: ["23:59","00:00"]
Output: 1
Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.
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
private:
    int transfer(string timePoint) {
        int found = timePoint.find(":");
        int hour = stoi(timePoint.substr(0, found));
        int minutes = stoi(timePoint.substr(found + 1));
        return hour * 60 + minutes;
    }

public:
    int findMinDifference(vector<string> &timePoints) {
        vector<bool> minutes(1440, false);
        for (string timePoint: timePoints) {
            int minute = transfer(timePoint);
            if (minutes[minute]) {
                return 0;
            }
            minutes[minute] = true;
        }

        int first = -1;
        int last = -1;
        int prev = -1;
        int result = INT_MAX;
        for (int i = 0; i < minutes.size(); i++) {
            if (minutes[i]) {
                if (prev == -1) {
                    first = i;
                    last = i;
                    prev = i;
                } else {
                    result = min(result, i - prev);
                    prev = i;
                    last = i;
                }
            }
        }
        return min(result, 1440 - last + first);
    }
};
