//
//  meeting_rooms_II.cpp
//  C++
//
//  Created by Chenfu Xie on 3/1/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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

/*
 Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
 
 For example,
 Given [[0, 30],[5, 10],[15, 20]],
 return 2.
 */
  struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](Interval &i, Interval &j){return i.start < j.start;});
        priority_queue<int, vector<int>, greater<int>> min_heap;
        int result = 0;
        for(auto interval : intervals){
            while (!min_heap.empty() && min_heap.top() <= interval.start) {
                min_heap.pop();
            }
            min_heap.push(interval.end);
            result = max(result, (int)min_heap.size());
        }
        return result;
    }
};
