/*
155. Min Stack
https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
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
#include <map>
using namespace std;

class MinStack {
private:
    stack<int> num_stk_;
    stack<int> min_stk_;

public:
    MinStack() {
    }

    void push(int x) {
        if (num_stk_.empty()) {
            num_stk_.push(x);
            min_stk_.push(x);
            return;
        }

        num_stk_.push(x);
        int cur_min = min_stk_.top();
        min_stk_.push(min(cur_min, x));
    }

    void pop() {
        if (num_stk_.empty()) {
            return;
        }
        min_stk_.pop();
        num_stk_.pop();
    }

    int top() {
        if (num_stk_.empty()) {
            return 0;
        }
        return num_stk_.top();
    }

    int getMin() {
        if (min_stk_.empty()) {
            return 0;
        }
        return min_stk_.top();
    }
};