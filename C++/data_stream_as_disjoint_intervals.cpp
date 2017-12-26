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
class SummaryRanges {
private:
    vector<Interval> intervals;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
    }

    void addNum(int val) {
        auto it = lower_bound(intervals.begin(), intervals.end(), Interval(val, val), [](Interval& a, Interval& b) {
            return a.start > b.start;
        });

        if (it == intervals.end()) {
            if (intervals.front().start <= val + 1) {
                intervals.front().start = val;
                return;
            }
            intervals.insert(intervals.begin(), Interval(val, val));
        }
        else if (val - 1 <= it -> end) {
            it -> end = max(it -> end, val);
        }
        else {
            it += 1;
            intervals.insert(it, Interval(val, val));
        }

        if (it + 1 != intervals.end() && it -> end + 1 >= (it + 1) -> start) {
            (it + 1) -> start = it -> start;
            intervals.erase(it);
        }

        return;
    }

    vector<Interval> getIntervals() {
        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */