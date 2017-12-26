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
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if (intervals.size() == 0) {
            return 0;
        }

        sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b) {
            return a.start < b.start || a.end < b.end;
        });

        int result = 1;
        int preEnd = intervals[0].end;
        for (int i = 1; i < intervals.size(); i++) {
            if (preEnd <= intervals[i].start) {
                result += 1;
                preEnd = intervals[i].end;
            }
        }
        return intervals.size() - result;
    }
};