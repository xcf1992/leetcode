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
    int transfer(string timePoint) { // 23:59
        int found = timePoint.find(":");
        int hour = stoi(timePoint.substr(0, found));
        int minutes = stoi(timePoint.substr(found + 1));
        return hour * 60 + minutes;
    }
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<bool> minutes(1440, false);

        for (string timePoint : timePoints) {
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
                }
                else {
                    result = min(result, i - prev);
                    prev = i;
                    last = i;
                }
            }
        }
        return min(result, 1440 - last + first);
    }
};