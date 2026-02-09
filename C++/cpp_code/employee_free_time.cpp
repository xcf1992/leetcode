/*
759. Employee Free Time
https://leetcode.com/problems/employee-free-time/

We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted
order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays.
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't
include intervals like [5, 5] in our answer, as they have zero length.



Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]


Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8
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
#include <climits>
#include <map>
using namespace std;

struct Interval {
    int start;
    int end;

    Interval() : start(0), end(0) {
    }

    Interval(int s, int e) : start(s), end(e) {
    }
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedules) {
        map<int, int> timeline;
        for (const vector<Interval>& schedule : schedules) {
            for (Interval itvl : schedule) {
                timeline[itvl.start] += 1;
                timeline[itvl.end] -= 1;
            }
        }

        vector<Interval> rst;
        int workers = 0;
        for (pair<int, int> busy : timeline) {
            workers += busy.second;
            if (workers == 0) {
                rst.push_back(Interval(busy.first, 0));
            } else if (!rst.empty() && rst.back().end == 0) {
                rst.back().end = busy.first;
            }
        }

        if (rst.back().end == 0) {
            rst.pop_back();
        }
        return rst;
    }
};

class Solution1 {
public:
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>>& schedules) {
        vector<Interval*> intervals;
        for (vector<Interval*> schedule : schedules) {
            for (Interval* it : schedule) {
                intervals.push_back(it);
            }
        }

        sort(intervals.begin(), intervals.end(), [](Interval* a, Interval* b) {
            return a->start < b->start or (a->start == b->start and a->end < b->end);
        });

        vector<Interval*> result;
        int end = intervals[0]->end;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i]->start > end) {
                result.push_back(new Interval(end, intervals[i]->start));
            }
            end = max(end, intervals[i]->end);
        }
        return result;
    }
};