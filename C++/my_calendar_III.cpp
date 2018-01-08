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

class MyCalendarThree {
private:
    map<int, int> events;
public:
    MyCalendarThree() {}
    
    int book(int start, int end) {
        events[start] += 1;
        events[end] -= 1;
        int booked = 0;
        int result = 0;
        for (auto &event : events) {
            booked += event.second;
            result = max(result, booked);
        }
        return result;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */
