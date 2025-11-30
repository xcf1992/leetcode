/*
225. Implement Stack using Queues
https://leetcode.com/problems/implement-stack-using-queues/

Implement the following operations of a stack using queues.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.

Example:
MyStack stack = new MyStack();
stack.push(1);
stack.push(2);
stack.top();   // returns 2
stack.pop();   // returns 2
stack.empty(); // returns false

Notes:
You must use only standard operations of a queue --
which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language,
queue may not be supported natively.
You may simulate a queue by using a list or deque (double-ended queue),
as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
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
using namespace std;

class MyStack {
private:
    queue<int> stk;

public:
    /** Initialize your data structure here. */
    MyStack() {
    }

    /** Push element x onto stack. */
    void push(int x) {
        int curSize = stk.size();
        stk.push(x);
        for (int i = 0; i < curSize; ++i) {
            stk.push(stk.front());
            stk.pop();
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int result = top();
        stk.pop();
        return result;
    }

    /** Get the top element. */
    int top() {
        return stk.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return stk.empty();
    }
};