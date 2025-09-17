/*
2. Add Two Numbers
https://leetcode.com/problems/add-two-numbers/

You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr or l2 == nullptr) {
            return l1 == nullptr ? l2 : l1;
        }

        int carry = 0;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* head = nullptr;
        ListNode* cur = head;
        while (cur1 != nullptr or cur2 != nullptr or carry != 0) {
            int sum = carry;
            if (cur1 != nullptr) {
                sum += cur1 -> val;
                cur1 = cur1 -> next;
            }
            if (cur2 != nullptr) {
                sum += cur2 -> val;
                cur2 = cur2 -> next;
            }

            ListNode* node = new ListNode(sum % 10);
            if (head == nullptr) {
                head = node;
                cur = head;
            }
            else {
                cur -> next = node;
            }
            cur = node;
            carry = sum / 10;
        }
        return head;
    }
};
