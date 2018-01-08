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
    vector<pair<int, int>> events;
public:
    MyCalendar() {
    }
    
    bool book(int start, int end) {
        if (events.empty()) {
            events.push_back(pair<int, int>(start, end));
            return true;
        }
        if (end <= events.front().first) {
            events.insert(events.begin(), pair<int, int>(start, end));
            return true;
        }
        if (start >= events.back().second) {
            events.insert(events.end(), pair<int, int>(start, end));
            return true;
        }
        
        int st = 0;
        int en = events.size();
        while (st < en) {
            int mi = st + (en - st) / 2;
            if (start == events[mi].first) {
                return false;
            }
            if (start < events[mi].first) {
                en = mi;
            }
            else {
                st = mi + 1;
            }
        }
        
        if (end <= events[en].first && start >= events[en - 1].second) {
            events.insert(events.begin() + en, pair<int, int>(start, end));
            return true;
        }
        return false;
    }
};
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
