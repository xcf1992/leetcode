/*
https://leetcode.com/problems/design-most-recently-used-queue/description/
1756. Design Most Recently Used Queue

Design a queue-like data structure that moves the most recently used element to the end of the queue.

Implement the MRUQueue class:

MRUQueue(int n) constructs the MRUQueue with n elements: [1,2,3,...,n].
int fetch(int k) moves the kth element (1-indexed) to the end of the queue and returns it.


Example 1:

Input:
["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
[[8], [3], [5], [2], [8]]
Output:
[null, 3, 6, 2, 2]

Explanation:
MRUQueue mRUQueue = new MRUQueue(8); // Initializes the queue to [1,2,3,4,5,6,7,8].
mRUQueue.fetch(3); // Moves the 3rd element (3) to the end of the queue to become [1,2,4,5,6,7,8,3] and returns it.
mRUQueue.fetch(5); // Moves the 5th element (6) to the end of the queue to become [1,2,4,5,7,8,3,6] and returns it.
mRUQueue.fetch(2); // Moves the 2nd element (2) to the end of the queue to become [1,4,5,7,8,3,6,2] and returns it.
mRUQueue.fetch(8); // The 8th element (2) is already at the end of the queue so just return it.


Constraints:

1 <= n <= 2000
1 <= k <= n
At most 2000 calls will be made to fetch.


Follow up: Finding an O(n) algorithm per fetch is a bit easy. Can you find an algorithm with a better complexity for
each fetch call?
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
#include <numeric>
using namespace std;

class MyListNode {
public:
    int val_;
    MyListNode* pre_;
    MyListNode* next_;

    MyListNode(int x) : val_(x), pre_(nullptr), next_(nullptr) {
    }
};

class MRUQueue {
public:
    MRUQueue(int n) {
        pre_head = new MyListNode(-1);
        MyListNode* pre = pre_head;
        for (int i = 1; i <= n; i++) {
            MyListNode* cur = new MyListNode(i);
            cur->pre_ = pre;
            pre->next_ = cur;
            pre = cur;
        }

        pre_head->pre_ = pre;
        pre->next_ = pre_head;
    }

    int fetch(int k) {
        MyListNode* cur = pre_head;
        for (int i = 1; i <= k; i++) {
            cur = cur->next_;
        }

        cur->pre_->next_ = cur->next_;
        cur->next_->pre_ = cur->pre_;

        pre_head->pre_->next_ = cur;
        cur->pre_ = pre_head->pre_;

        pre_head->pre_ = cur;
        cur->next_ = pre_head;
        return cur->val_;
    }
private:
    MyListNode* pre_head;
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */