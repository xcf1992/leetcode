/*
232. Implement Queue using Stacks
https://leetcode.com/problems/implement-queue-using-stacks/

Implement the following operations of a queue using stacks.
push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.

Example:
MyQueue queue = new MyQueue();
queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false

Notes:
You must use only standard operations of a stack --
which means only push to top, peek/pop from top, size, and is empty operations are valid.

Depending on your language, stack may not be supported natively.
You may simulate a stack by using a list or deque (double-ended queue),
as long as you use only standard operations of a stack.
You may assume that all operations are valid
(for example, no pop or peek operations will be called on an empty queue).
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
using namespace std;

class MyQueue {
private:
    stack<int> input;
    stack<int> output;
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        input.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int result = peek();
        output.pop();
        return result;
    }

    /** Get the front element. */
    int peek() {
       if (output.empty()) {
           while (!input.empty()) {
               output.push(input.top());
               input.pop();
           }
       }
       return output.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return input.empty() and output.empty();
    }
};

class MyQueue1 {
private:
    stack<int> queue;
public:
    /** Initialize your data structure here. */
    MyQueue1() {

    }

    // Push element x to the back of queue.
    void push(int x) {
        stack<int> reverse;
        while (!queue.empty()) {
            reverse.push(queue.top());
            queue.pop();
        }
        reverse.push(x);
        while (!reverse.empty()) {
            queue.push(reverse.top());
            reverse.pop();
        }
    }

    // Removes the element from in front of queue.
    void pop(void) {
        queue.pop();
    }

    // Get the front element.
    int peek(void) {
       return queue.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return queue.empty();
    }
};
/*
Your MyQueue object will be instantiated and called as such:
MyQueue* obj = new MyQueue();
obj->push(x);
int param_2 = obj->pop();
int param_3 = obj->peek();
bool param_4 = obj->empty();
*/