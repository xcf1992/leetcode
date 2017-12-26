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


class Queue {
private:
    stack<int> queue;
public:
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
        return;
    }

    // Removes the element from in front of queue.
    void pop(void) {
        queue.pop();
        return;
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