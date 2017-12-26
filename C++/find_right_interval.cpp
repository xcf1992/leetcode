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
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<int> result;
        map<int, int> mapIntervals;
        for (int i = 0; i < intervals.size(); i++) {
            mapIntervals.emplace(intervals[i].start, i);
        }

        for (Interval interval : intervals) {
            auto it = mapIntervals.lower_bound(interval.end);
            result.push_back(it == mapIntervals.end() ? -1 : it -> second);
        }
        return result;
    }
};