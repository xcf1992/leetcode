/*
253. Meeting Rooms II
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
find the minimum number of conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
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
#include <map>
using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& i, vector<int>& j) {
            return i[0] < j[0];
        });

        priority_queue<int, vector<int>, greater<int>> min_heap;
        int result = 0;
        for (vector<int>& interval : intervals) {
            while (!min_heap.empty() and interval[0] >= min_heap.top()) { // some meetings have ended already
                min_heap.pop();
            }
            min_heap.push(interval[1]);
            result = max(result, (int)min_heap.size());
        }
        return result;
    }
};
