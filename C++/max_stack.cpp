/*
 Design a max stack that supports push, pop, top, peekMax and popMax.

 push(x) -- Push element x onto stack.
 pop() -- Remove the element on top of the stack and return it.
 top() -- Get the element on the top.
 peekMax() -- Retrieve the maximum element in the stack.
 popMax() -- Retrieve the maximum element in the stack, and remove it. If you find more than one maximum elements, only remove the top-most one.
 Example 1:
 MaxStack stack = new MaxStack();
 stack.push(5);
 stack.push(1);
 stack.push(5);
 stack.top(); -> 5
 stack.popMax(); -> 5
 stack.top(); -> 1
 stack.peekMax(); -> 5
 stack.pop(); -> 1
 stack.top(); -> 5
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

class MaxStack {
    stack<int> elements;
    stack<int> maxElements;
public:
    /* initialize your data structure here.*/
    MaxStack() {

    }

    void push(int x) {
        elements.push(x);
        if (maxElements.empty() or x >= maxElements.top()) {
            maxElements.push(x);
        }
        else {
            maxElements.push(maxElements.top());
        }
    }

    int pop() {
        int result = elements.top();
        elements.pop();
        maxElements.pop();
        return result;
    }

    int top() {
        return elements.top();
    }

    int peekMax() {
        return maxElements.top();
    }

    int popMax() {
        int maxVal = maxElements.top();
        stack<int> temp;

        while (elements.top() != maxVal) {
            temp.push(elements.top());
            elements.pop();
            maxElements.pop();
        }
        elements.pop();
        maxElements.pop();

        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }

        return maxVal;
    }
};

/*
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack obj = new MaxStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.peekMax();
 * int param_5 = obj.popMax();
*/
