/*
25. Reverse Nodes in k-Group
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Note:

Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void reverse(ListNode* head, ListNode* tail) {
        if (head == tail) {
            return;
        }

        ListNode* suc = head -> next;
        reverse(suc, tail);
        suc -> next = head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr or head -> next == nullptr or k == 1) {
            return head;
        }

        ListNode* preHead = new ListNode(-1);
        preHead -> next = head;
        ListNode* tail = head;
        ListNode* pre = preHead;
        int len = 1;
        while (tail != nullptr) {
            tail = tail -> next;
            len += 1;
            if (len == k and tail != nullptr) {
                ListNode* curHead = pre -> next;
                ListNode* cur = tail -> next;
                reverse(curHead, tail);
                curHead -> next = cur;
                pre -> next = tail;

                pre = curHead;
                tail = cur;
                len = 1;
            }
        }
        return preHead -> next;
    }
};