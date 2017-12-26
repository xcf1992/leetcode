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


class Stack {
private:
    queue<int> queueStack;
public:
    // Push element x onto stack.
    void push(int x) {
        queue<int> reverse;
        while (!queueStack.empty()) {
            reverse.push(queueStack.front());
            queueStack.pop();
        }
        queueStack.push(x);

        while (!reverse.empty()) {
            queueStack.push(reverse.front());
            reverse.pop();
        }
        return;
    }

    // Removes the element on top of the stack.
    void pop() {
        queueStack.pop();
        return;
    }

    // Get the top element.
    int top() {
        return queueStack.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return queueStack.empty();
    }
};

int main() {
    Solution s;
    return 0;
}