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

    int search(int target) {
        int left = 0;
        int right = intervals.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (intervals[mid][0] == target) {
                return mid;
            }

            if (intervals[mid][0] > target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}

    void addNum(int val) {
        int n = intervals.size();
        if (n == 0) {
            intervals.push_back({val, val});
            return;
        }

        if (val < intervals[0][0]) {
            if (val + 1 == intervals[0][0]) {
                intervals[0][0] = val;
                return;
            }
            intervals.insert(intervals.begin(), {val, val});
            return;
        }

        if (val > intervals[n - 1][0]) {
            if (val <= intervals[n - 1][1]) {
                return;
            }
            if (val == intervals[n - 1][1] + 1) {
                intervals[n - 1][1] = val;
                return;
            }
            intervals.push_back({val, val});
            return;
        }

        int pos = search(val);
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