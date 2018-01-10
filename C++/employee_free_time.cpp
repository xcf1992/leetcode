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

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedules) {
        map<int, int> timeline;
        for (auto schedule : schedules) {
            for (Interval interval : schedule) {
                timeline[interval.start] += 1;
                timeline[interval.end] -= 1;
            }
        }
        
        vector<Interval> result;
        int workers = 0;
        for (pair<int, int> busy : timeline) {
            workers += busy.second;
            if (workers == 0) {
                result.push_back(Interval(busy.first, 0));
            }
            else if (!result.empty() && result.back().end == 0) {
                result.back().end = busy.first;
            }
        }
        
        if (result.back().end == 0) {
            result.pop_back();
        }
        return result;
    }
};
