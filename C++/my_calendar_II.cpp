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

class MyCalendarTwo {
private:
    map<int, int> events;
public:
    MyCalendarTwo() {}
    
    bool book(int start, int end) {
        events[start] += 1;
        events[end] -= 1;
        int booked = 0;
        for (auto &event : events) {
            booked += event.second;
            if (booked == 3) {
                events[start] -= 1;
                events[end] += 1;
                return false;
            }
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */
