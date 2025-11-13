/*
https://leetcode.com/problems/two-best-non-overlapping-events/description/
2054. Two Best Non-Overlapping Events

You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event
starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can
choose at most two non-overlapping events to attend such that the sum of their values is maximized.

Return this maximum sum.

Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and
the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at
or after t + 1.



Example 1:


Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
Example 2:

Example 1 Diagram
Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5.
Example 3:


Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.


Constraints:

2 <= events.length <= 105
events[i].length == 3
1 <= startTimei <= endTimei <= 109
1 <= valuei <= 106
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        });

        int rst = 0;
        int max_val = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (const vector<int>& event : events) {
            int start = event[0];
            int end = event[1];
            int cur_val = event[2];
            while (!pq.empty() && pq.top().first < start) {
                max_val = max(max_val, pq.top().second);
                pq.pop();
            }

            rst = max(rst, max_val+cur_val);
            pq.push({end, cur_val});
        }
        return rst;
    }
};