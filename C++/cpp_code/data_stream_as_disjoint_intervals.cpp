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

NOTE:
input types have been changed on April 15, 2019.
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
/*
First, run lower_bound let it point to interval (8,9) because 8 is the first element that is >= 7

(0,2) (4,6) (8,9) (12,15)    temp = (7, 7)
             ^
We decrement it because the previous interval can merge 7

(0,2) (4,6) (8,9) (12,15)    temp = (7, 7)
       ^
Now, it points to the first mergeable interval (if there is one). In this case, (4,6).
While this interval is mergeable, merge (4,6) with temp to get

(0,2) (8,9) (12,15)          temp = (4, 7)
       ^
Merge (8,9) with temp to get

(0,2) (12,15)                temp = (4, 9)
       ^
Can't merge anymore, insert temp

(0,2) (4,9) (12,15)          temp = (4, 9)
Done.
*/
class SummaryRanges {
private:
    vector<vector<int>> intervals;

    int search(int target) {
        int left = 0;
        int right = intervals.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (intervals[mid][0] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

public:
    /* Initialize your data structure here.*/
    SummaryRanges() {
    }

    void addNum(int val) {
        if (intervals.empty()) {
            intervals.push_back({val, val});
            return;
        }

        int index = search(val);
        if (index > 0 and intervals[index - 1][1] + 1 >= val) {
            index -= 1;
        }

        int start = val;
        int end = val;
        while (index < intervals.size() and intervals[index][0] <= val + 1 and val - 1 <= intervals[index][1]) {
            start = min(intervals[index][0], start);
            end = max(end, intervals[index][1]);
            intervals.erase(intervals.begin() + index);
        }
        intervals.insert(intervals.begin() + index, {start, end});
    }

    vector<vector<int>> getIntervals() {
        return intervals;
    }
};

/*
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */