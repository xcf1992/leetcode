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
#include <stdio.h>
#include <map>
using namespace std;

class MinStack {
private:
    stack<int> numStack;
    stack<int> minStack;

public:
    void push(int x) {
        if (numStack.empty()) {
            numStack.push(x);
            minStack.push(x);
            return;
        }

        numStack.push(x);
        if (minStack.top() >= x) {
            minStack.push(x);
        }
    }

    void pop() {
        if (numStack.empty()) {
            return;
        }
        if (numStack.top() == minStack.top()) {
            minStack.pop();
        }
        numStack.pop();
    }

    int top() {
        if (numStack.empty()) {
            return 0;
        }
        return numStack.top();
    }

    int getMin() {
        if (minStack.empty()) {
            return 0;
        }
        return minStack.top();
    }
};