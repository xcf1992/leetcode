/*
716. Max Stack
https://leetcode.com/problems/max-stack/

Design a max stack that supports push, pop, top, peekMax and popMax.
push(x) -- Push element x onto stack.
pop() -- Remove the element on top of the stack and return it.
top() -- Get the element on the top.
peekMax() -- Retrieve the maximum element in the stack.
popMax() -- Retrieve the maximum element in the stack, and remove it.
            If you find more than one maximum elements, only remove the top-most one.

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
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

class MaxStack {
private:
    set<pair<int, int>> nums_;
    set<pair<int, int>> max_stk_;
    int idx_;

public:
    MaxStack() {
        idx_ = 0;
    }

    void push(int x) {
        nums_.insert({idx_, x});
        max_stk_.insert({x, idx_});
        idx_++;
    }

    int pop() {
        pair<int, int> last_val = *nums_.rbegin();
        nums_.erase(last_val);
        max_stk_.erase({last_val.second, last_val.first});
        return last_val.second;
    }

    int top() {
        return nums_.rbegin()->second;
    }

    int peekMax() {
        return max_stk_.rbegin()->first;
    }

    int popMax() {
        pair<int, int> max_num = *max_stk_.rbegin();
        max_stk_.erase(max_num);
        nums_.erase({max_num.second, max_num.first});
        return max_num.first;
    }
};

class MaxStack {
    stack<int> nums_;
    stack<int> max_val_;

public:
    /* initialize your data structure here.*/
    MaxStack() {
    }

    void push(int x) {
        nums_.push(x);
        if (max_val_.empty() or x >= max_val_.top()) {
            max_val_.push(x);
        } else {
            max_val_.push(max_val_.top());
        }
    }

    int pop() {
        int result = nums_.top();
        nums_.pop();
        max_val_.pop();
        return result;
    }

    int top() {
        return nums_.top();
    }

    int peekMax() {
        return max_val_.top();
    }

    int popMax() {
        int cur_max = max_val_.top();
        stack<int> temp;
        while (nums_.top() != cur_max) {
            temp.push(nums_.top());
            nums_.pop();
            max_val_.pop();
        }
        nums_.pop();
        max_val_.pop();

        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
        return cur_max;
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