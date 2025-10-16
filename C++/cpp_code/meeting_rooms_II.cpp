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

class Solution1 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        size_t n = intervals.size();
        if (n <= 1) {
            return n;
        }

        vector<int> i_start;
        vector<int> i_end;
        for (vector<int>& in : intervals) {
            i_start.push_back(in[0]);
            i_end.push_back(in[1]);
        }
        sort(i_start.begin(), i_start.end());
        sort(i_end.begin(), i_end.end());

        int result = 0;
        for (int cur : i_start) {
            int start_cnt = upper_bound(i_start.begin(), i_start.end(), cur) - i_start.begin();
            int end_cnt = upper_bound(i_end.begin(), i_end.end(), cur) - i_end.begin();
            result = max(result, start_cnt - end_cnt);
        }
        return result;
    }
};