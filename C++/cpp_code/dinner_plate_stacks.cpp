/*
1172. Dinner Plate Stacks
You have an infinite number of stacks arranged in a row and numbered (left to right) from 0,
each of the stacks has the same maximum capacity.

Implement the DinnerPlates class:

DinnerPlates(int capacity)
Initializes the object with the maximum capacity of the stacks.

void push(int val)
pushes the given positive integer val into the leftmost stack with size less than capacity.

int pop()
returns the value at the top of the rightmost non-empty stack and removes it from that stack,
and returns -1 if all stacks are empty.

int popAtStack(int index)
returns the value at the top of the stack with the given index and removes it from that stack,
and returns -1 if the stack with that given index is empty.

Example:
Input:
["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
[[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
Output:
[null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]

Explanation:
DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
D.push(1);
D.push(2);
D.push(3);
D.push(4);
D.push(5);         // The stacks are now:  2  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 2.  The stacks are now:     4
                                                       1  3  5
                                                       ﹈ ﹈ ﹈
D.push(20);        // The stacks are now: 20  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.push(21);        // The stacks are now: 20  4 21
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.popAtStack(2);   // Returns 21.  The stacks are now:     4
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.pop()            // Returns 5.  The stacks are now:      4
                                                        1  3
                                                        ﹈ ﹈
D.pop()            // Returns 4.  The stacks are now:   1  3
                                                        ﹈ ﹈
D.pop()            // Returns 3.  The stacks are now:   1
                                                        ﹈
D.pop()            // Returns 1.  There are no stacks.
D.pop()            // Returns -1.  There are still no stacks.


Constraints:

1 <= capacity <= 20000
1 <= val <= 20000
0 <= index <= 100000
At most 200000 calls will be made to push, pop, and popAtStack.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class DinnerPlates {
    // from god lee but it does not work, check back later
public:
    int c;
    map<int, vector<int> > m;
    set<int> available;

    DinnerPlates(int capacity) {
        c = capacity;
    }

    void push(int val) {
        if (!available.size()) {
            available.insert(m.size());
        }

        m[*available.begin()].push_back(val);
        if (m[*available.begin()].size() == c) {
            available.erase(available.begin());
        }
    }

    int pop() {
        if (m.size() == 0) {
            return -1;
        }
        return popAtStack(m.rbegin()->first);
    }

    int popAtStack(int index) {
        if (m[index].size() == 0) {
            return -1;
        }

        int val = m[index].back();
        m[index].pop_back();
        available.insert(index);
        if (m[index].size() == 0) {
            m.erase(index);
        }
        return val;
    }
};

class DinnerPlates1 {
    // 17.40%
private:
    vector<stack<int> > plates;
    int limit = 0;
    map<int, int> count;

public:
    DinnerPlates(int capacity) {
        limit = capacity;
    }

    void push(int val) {
        if (count.empty()) {
            stack<int> stk({val});
            plates.push_back(stk);
            if (plates.back().size() < limit) {
                count[plates.size() - 1] = 1;
            }
            return;
        }

        auto it = count.begin();
        plates[it->first].push(val);
        if (plates[it->first].size() >= limit) {
            count.erase(it);
        } else {
            count[it->first] += 1;
        }
    }

    int pop() {
        if (plates.empty()) {
            return -1;
        }

        int result = plates.back().top();
        plates.back().pop();
        while (!plates.empty() and
        plates.back().empty()
        )
        {
            count.erase(plates.size() - 1);
            plates.pop_back();
        }
        if (!plates.empty()) {
            count[plates.size() - 1] = plates[plates.size() - 1].size();
        }
        return result;
    }

    int popAtStack(int index) {
        if (index >= plates.size()) {
            return -1;
        }

        if (index == plates.size() - 1) {
            return pop();
        }

        if (plates[index].empty()) {
            return -1;
        }

        int result = plates[index].top();
        plates[index].pop();
        count[index] = plates[index].size();
        return result;
    }
};

/*
* Your DinnerPlates object will be instantiated and called as such:
* DinnerPlates* obj = new DinnerPlates(capacity);
* obj->push(val);
* int param_2 = obj->pop();
* int param_3 = obj->popAtStack(index);
*/