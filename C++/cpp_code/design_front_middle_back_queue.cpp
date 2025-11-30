/*
1670. Design Front Middle Back Queue
https://leetcode.com/problems/design-front-middle-back-queue/

Design a queue that supports push and pop operations in the front, middle, and back.

Implement the FrontMiddleBack class:
FrontMiddleBack() Initializes the queue.
void pushFront(int val) Adds val to the front of the queue.
void pushMiddle(int val) Adds val to the middle of the queue.
void pushBack(int val) Adds val to the back of the queue.
int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.

Notice that when there are two middle position choices,
the operation is performed on the frontmost middle position choice. For example:

Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5, 6].

Example 1:
Input:
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle",
"popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
Output:
[null, null, null, null, null, 1, 3, 4, 2, -1]
Explanation:
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // return 1 -> [4, 3, 2]
q.popMiddle();    // return 3 -> [4, 2]
q.popMiddle();    // return 4 -> [2]
q.popBack();      // return 2 -> []
q.popFront();     // return -1 -> [] (The queue is empty)

Constraints:
1 <= val <= 109
At most 1000 calls will be made to pushFront, pushMiddle, pushBack, popFront, popMiddle, and popBack.
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
#include <cfloat>
#include <climits>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;

class FrontMiddleBackQueue {
private:
    deque<int> first;
    deque<int> second;

    void rebalance() {
        int s1 = first.size();
        int s2 = second.size();
        if (s1 == s2) {
            return;
        }

        if (s1 > s2) {
            second.push_front(first.back());
            first.pop_back();
            return;
        }

        if (s1 + 1 < s2) {
            first.push_back(second.front());
            second.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {
        first.clear();
        second.clear();
    }

    void pushFront(int val) {
        first.push_front(val);
        rebalance();
    }

    void pushMiddle(int val) {
        first.push_back(val);
        rebalance();
    }

    void pushBack(int val) {
        second.push_back(val);
        rebalance();
    }

    int popFront() {
        if (!first.empty()) {
            int val = first.front();
            first.pop_front();
            rebalance();
            return val;
        }
        if (second.empty()) {
            return -1;
        }
        int val = second.front();
        second.pop_front();
        rebalance();
        return val;
    }

    int popMiddle() {
        if (first.size() == second.size()) {
            if (!first.empty()) {
                int val = first.back();
                first.pop_back();
                rebalance();
                return val;
            }
            return -1;
        }

        int val = second.front();
        second.pop_front();
        rebalance();
        return val;
    }

    int popBack() {
        if (!second.empty()) {
            int val = second.back();
            second.pop_back();
            rebalance();
            return val;
        }
        if (first.empty()) {
            return -1;
        }
        int val = first.back();
        first.back();
        rebalance();
        return val;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */