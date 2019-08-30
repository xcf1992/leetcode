/*
1171. Remove Zero Sum Consecutive Nodes from Linked List
Given the head of a linked list,
we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.

(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:

Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:

Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:

Input: head = [1,2,3,-3,-2]
Output: [1]


Constraints:

The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.
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
#include "extra_data_types.hpp"
#include <numeric>
using namespace std;

class Solution { // 89%
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if (head == nullptr or (head -> next == nullptr and head -> val == 0)) {
            return nullptr;
        }

        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode* curNode = dummy;

        unordered_map<int, ListNode*> preSum;
        int curSum = 0;
        while (curNode != nullptr) {
            curSum += curNode -> val;
            if (preSum.find(curSum) != preSum.end()) {
                curNode = preSum[curSum] -> next;
                int temp = curSum + curNode -> val;
                while (temp != curSum) {
                    preSum.erase(temp);
                    curNode = curNode -> next;
                    temp += curNode -> val;
                }
                preSum[curSum] -> next = curNode -> next;
            }
            else {
                preSum[curSum] = curNode;
            }
            curNode = curNode -> next; // remember to move curnode forward
        }
        return dummy -> next;
    }
};

class Solution1 { // 27%
private:
    vector<ListNode*> find(ListNode* head) {
        if (head == nullptr) {
            return {};
        }

        unordered_map<int, ListNode*> sum;
        int curSum = 0;
        ListNode* curNode = head;
        while (curNode != nullptr) {
            curSum += curNode -> val;
            if (curSum == 0) {
                return {curNode};
            }

            if (sum.find(curSum) != sum.end()) {
                return {sum[curSum], curNode};
            }
            sum[curSum] = curNode;
            curNode = curNode -> next;
        }
        return {};
    }
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if (head == nullptr or (head -> next == nullptr and head -> val == 0)) {
            return nullptr;
        }

        ListNode* dummy = new ListNode(INT_MIN);
        dummy -> next = head;
        vector<ListNode*> target = find(dummy -> next);
        while (!target.empty()) {
            if (target.size() == 1) {
                dummy -> next = target[0] -> next;
            }
            else {
                ListNode* cur = dummy -> next;
                while (cur != target[0]) {
                    cur = cur -> next;
                }
                cur -> next = target[1] -> next;
            }
            target = find(dummy -> next);
        }
        return dummy -> next;
    }
};
