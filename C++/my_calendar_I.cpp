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

class MyCalendar {
private:
    set<pair<int, int>> events;
public:
    MyCalendar() {
    }
    
    bool book(int start, int end) {
        auto it = events.lower_bound({start, end});
        
        if (it != events.end() and it -> first < end) {
            return false;
        }

        if (it != events.begin() and (--it) -> second > start) {
            return false;
        }

        events.insert({start, end});
        return true;
    }
};
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
