/*
143. Reorder List
https://leetcode.com/problems/reorder-list/

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
You may not modify the values in the list's nodes,
only nodes itself may be changed.

Example 1:
Given 1 -> 2 -> 3 -> 4, reorder it to 1 -> 4 -> 2 -> 3.

Example 2:
Given 1 -> 2 -> 3 -> 4 -> 5, reorder it to 1 -> 5 -> 2 -> 4 -> 3.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr or head -> next == nullptr or head -> next -> next == nullptr) {
            return;
        }

        ListNode* dummy1 = new ListNode(-1);
        dummy1 -> next = head;
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* pre = dummy1;
        while (fast != nullptr) {
            fast = fast -> next;
            if (fast != nullptr) {
                fast = fast -> next;
                slow = slow -> next;
                pre = pre -> next;
            }
        }
        pre -> next = nullptr;

        ListNode* dummy2 = new ListNode(-2);
        ListNode* cur = slow;
        while (cur != nullptr) {
            ListNode* after = cur -> next;
            cur -> next = dummy2 -> next;
            dummy2 -> next = cur;
            cur = after;
        }

        ListNode* cur1 = dummy1 -> next;
        ListNode* cur2 = dummy2 -> next;
        while (cur1 -> next != nullptr) {
            ListNode* suc = cur1 -> next;
            cur1 -> next = cur2;
            cur2 = cur2 -> next;
            cur1 -> next -> next = suc;
            cur1 = suc;
        }
        cur1 -> next = cur2;
    }
};
