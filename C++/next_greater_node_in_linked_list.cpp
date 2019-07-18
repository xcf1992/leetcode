/*
 1019. Next Greater Node In Linked List
 We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.

 Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.  If such a j does not exist, the next larger value is 0.

 Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).

 Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.



 Example 1:

 Input: [2,1,5]
 Output: [5,5,0]
 Example 2:

 Input: [2,7,4,3,5]
 Output: [7,0,5,5,0]
 Example 3:

 Input: [1,7,5,1,9,2,5,1]
 Output: [7,9,9,9,0,5,0,0]


 Note:

 1 <= node.val <= 10^9 for each node in the linked list.
 The given list has length in the range [0, 10000].
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        if (head == nullptr) {
            return {};
        }

        vector<int> result;
        stack<pair<int, int>> stk;
        ListNode* cur = head;
        int index = 0;
        while (cur != nullptr) {
            while (!stk.empty() and cur -> val > stk.top().second) {
                result[stk.top().first] = cur -> val;
                stk.pop();
            }
            stk.push({index, cur -> val});
            result.push_back(0);
            cur = cur -> next;
            index += 1;
        }
        return result;
    }
};

class Solution1 {
private:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr or head -> next == nullptr) {
            return head;
        }

        ListNode* nxt = head -> next;
        ListNode* newHead = reverseList(nxt);
        head -> next = nullptr;
        nxt -> next = head;
        return newHead;
    }
public:
    vector<int> nextLargerNodes(ListNode* head) {
        if (head == nullptr) {
            return {};
        }

        head = reverseList(head);
        stack<int> stk;
        stk.push(head -> val);
        vector<int> result;
        result.push_back(0);
        ListNode* cur = head -> next;
        while (cur != nullptr) {
            while (!stk.empty() and cur -> val > stk.top()) {
                stk.pop();
            }
            if (stk.empty()) {
                result.push_back(0);
            }
            else {
                result.push_back(stk.top());
            }
            stk.push(cur -> val);
            cur = cur -> next;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
