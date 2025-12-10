/*
1381. Design a Stack With Increment Operation
https://leetcode.com/problems/design-a-stack-with-increment-operation/

Design a stack which supports the following operations.

Implement the CustomStack class:
CustomStack(int maxSize)
Initializes the object with maxSize which is the maximum number of elements
in the stack or do nothing if the stack reached the maxSize.

void push(int x)
Adds x to the top of the stack if the stack hasn't reached the maxSize.

int pop()
Pops and returns the top of stack or -1 if the stack is empty.

void inc(int k, int val)
Increments the bottom k elements of the stack by val.
If there are less than k elements in the stack,
just increment all the elements in the stack.


Example 1:
Input
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
Output
[null,null,null,2,null,null,null,null,null,103,202,201,-1]
Explanation
CustomStack customStack = new CustomStack(3); // Stack is Empty []
customStack.push(1);                          // stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.push(3);                          // stack becomes [1, 2, 3]
customStack.push(4);                          // stack still [1, 2, 3], Don't add another elements as size is 4
customStack.increment(5, 100);                // stack becomes [101, 102, 103]
customStack.increment(2, 100);                // stack becomes [201, 202, 103]
customStack.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
customStack.pop();                            // return 202 --> Return top of the stack 102, stack becomes [201]
customStack.pop();                            // return 201 --> Return top of the stack 101, stack becomes []
customStack.pop();                            // return -1 --> Stack is empty return -1.

Constraints:
1 <= maxSize <= 1000
1 <= x <= 1000
1 <= k <= 1000
0 <= val <= 100
At most 1000 calls will be made to each method of increment, push and pop each separately.
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
/*
Use an additional array to record the increment value.
inc[i] means for all elements stack[0] ~ stack[i],
we should plus inc[i] when popped from the stack.
Then inc[i-1]+=inc[i], so that we will keep it from next pop.
*/
class CustomStack {
private:
    vector<int> stk;
    vector<int> inc;
    int n;

public:
    CustomStack(int maxSize) {
        n = maxSize;
    }

    void push(int x) {
        if (stk.size() == n) {
            return;
        }

        stk.push_back(x);
        inc.push_back(0);
    }

    int pop() {
        int i = stk.size() - 1;
        if (i < 0) {
            return -1;
        }

        if (i > 0) {
            inc[i - 1] += inc[i];
        }

        int result = stk[i] + inc[i];
        stk.pop_back();
        inc.pop_back();
        return result;
    }

    void increment(int k, int val) {
        int i = min(k, (int)stk.size()) - 1;
        if (i >= 0) {
            inc[i] += val;
        }
    }
};