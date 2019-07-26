/*
352. Data Stream as Disjoint Intervals
Given a data stream input of non-negative integers a1, a2, ..., an, ...,
summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

NOTE: input types have been changed on April 15, 2019.
Please reset to default code definition to get new method signature.
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

class SummaryRanges {
private:
    vector<vector<int>> intervals;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}

    void addNum(int val) {
        auto it = lower_bound(intervals.begin(), intervals.end(), val, [](vector<int>& a, int v) {
            return a[0] < v;
        });

        if (it == intervals.end()) {
            if (intervals.front()[0] <= val + 1) {
                intervals.front()[0] = val;
                return;
            }
            intervals.insert(intervals.begin(), {val, val});
        }
        else if (val - 1 <= (*it)[1]) {
            (*it)[1] = max((*it)[1], val);
        }
        else {
            it += 1;
            intervals.insert(it, {val, val});
        }

        if (it + 1 != intervals.end() && (*it)[1] + 1 >= (*next(it))[0]) {
            (*next(it))[0] = (*it)[0];
            intervals.erase(it);
        }
    }

    vector<vector<int>> getIntervals() {
        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */