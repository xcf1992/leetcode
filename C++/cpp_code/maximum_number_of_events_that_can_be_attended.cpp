/*
1353. Maximum Number of Events That Can Be Attended
https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/

Given an array of events where events[i] = [startDayi, endDayi].
Every event i starts at startDayi and ends at endDayi.

You can attend an event i at any day d where startTimei <= d <= endTimei.
Notice that you can only attend one event at any time d.

Return the maximum number of events you can attend.

Example 1:
Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.

Example 2:
Input: events= [[1,2],[2,3],[3,4],[1,2]]
Output: 4

Example 3:
Input: events = [[1,4],[4,4],[2,2],[3,4],[1,1]]
Output: 4

Example 4:
Input: events = [[1,100000]]
Output: 1

Example 5:
Input: events = [[1,1],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7]]
Output: 7

Constraints:
1 <= events.length <= 10^5
events[i].length == 2
1 <= events[i][0] <= events[i][1] <= 10^5
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
using namespace std;
/*
Sort events increased by start time.
Priority queue pq keeps the current open events.

Iterate from the day 1 to day 100000,
Each day, we add new events starting on day d to the queue pq.
Also we remove the events that are already closed.

Then we greedily attend the event that ends soonest.
If we can attend a meeting, we increment the result res.


Complexity
Time O(NlogN)
Space O(N)

Sort Events by Start Day:
First, we sort all events based on their start days. This helps us process events in chronological order, ensuring we
consider events as they become available.

Use a Min-Heap for End Days:
We use a priority queue (min-heap) to keep track of the end days of the events. This allows us to always pick the event
that ends the earliest, ensuring we can attend as many events as possible by freeing up days sooner.

Process Each Day:

Initialization: Start from day 1 and initialize a pointer to traverse the sorted events.
Add Events to Heap: For each day, add all events that start on or before the current day to the heap.
Remove Expired Events: Remove any events from the heap that have already ended before the current day.
Attend Earliest Ending Event: If there are events left in the heap, attend the one with the earliest end day (remove it
from the heap) and increment the count of attended events. Move to Next Day: After attending an event, move to the next
day and repeat the process until all events are processed.
*/

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        priority_queue<int, vector<int>, greater<int>> pq;  // 小顶堆，存 endDay

        int event_idx = 0;
        int n = events.size();
        int rst = 0;
        for (int day = 1; day <= 100000; day++) {
            // 1. 把今天开始的所有事件的 endDay 加入堆
            while (event_idx < n && events[event_idx][0] == day) {
                pq.push(events[event_idx][1]);
                event_idx++;
            }

            // 2. 移除已经过期的事件
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }

            // 3. 参加 endDay 最早的那个事件（贪心）
            if (!pq.empty()) {
                pq.pop();
                rst++;
            }

            // 提前终止：没有事件可处理了
            if (pq.empty() && event_idx >= n) {
                break;
            }
        }
        return rst;
    }
};

class Solution1 {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        int n = events.size();
        int cur_day = 0;
        int event_idx = 0;

        priority_queue<int, vector<int>, greater<int>> min_heap;
        int rst = 0;
        while (!min_heap.empty() || event_idx < n) {
            if (min_heap.empty()) {
                cur_day = events[event_idx][0];
            }

            while (event_idx < n && events[event_idx][0] <= cur_day) {
                min_heap.push(events[event_idx][1]);
                event_idx++;
            }

            min_heap.pop();  // attend the event ends earliest
            rst += 1;

            cur_day += 1;
            while (!min_heap.empty() && min_heap.top() < cur_day) {
                min_heap.pop();
            }
        }
        return rst;
    }
};
