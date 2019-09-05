/*
 715. Range Module
 A Range Module is a module that tracks ranges of numbers.
 Your task is to design and implement the following interfaces in an efficient manner.

 addRange(int left, int right)
 Adds the half-open interval [left, right),
 tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.

 queryRange(int left, int right)
 Returns true if and only if every real number in the interval [left, right) is currently being tracked.

 removeRange(int left, int right)
 Stops tracking every real number currently being tracked in the interval [left, right).

 Example 1:
 addRange(10, 20): null
 removeRange(14, 16): null
 queryRange(10, 14): true (Every number in [10, 14) is being tracked)
 queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
 queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)
 Note:

 A half open interval [left, right) denotes all real numbers left <= x < right.
 0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
 The total number of calls to addRange in a single test case is at most 1000.
 The total number of calls to queryRange in a single test case is at most 5000.
 The total number of calls to removeRange in a single test case is at most 1000.
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
#include <set>
#include <numeric>
using namespace std;

class RangeModule {
private:
    map<int, int> range;
public:
    RangeModule() {}

    void addRange(int left, int right) {
        removeRange(left, right);
        range[left] = right;
        auto it = range.find(left);
        if (it != range.begin() and prev(it) -> second == left) {
            it--;
            it -> second = right;
            range.erase(left);
        }
        if (it != prev(range.end()) and next(it) -> first == right) {
            it -> second = next(it) -> second;
            range.erase(next(it));
        }
    }

    bool queryRange(int left, int right) {
        if (range.empty()) {
            return false;
        }

        auto it = range.upper_bound(left);
        if (it == range.begin()) {
            return false;
        }
        it--;
        return it -> second >= right;
    }

    void removeRange(int left, int right) {
        if (range.empty()) {
            return;
        }

        auto it = range.lower_bound(left);
        if (it != range.begin()) {
            it--;
        }

        vector<int> removed;
        while (it != range.end() and it -> first < right) {
            if (it -> first < left and it -> second > left) {
                int temp = it -> second;
                it -> second = left;
                if (temp > right) {
                    range[right] = temp;
                }
            }
            else if (it -> first >= left) {
                removed.push_back(it -> first);
                if (it -> second > right) {
                    range[right] = it -> second;
                }
            }
            it++;
        }

        for (int i : removed) {
            range.erase(i);
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
*/
