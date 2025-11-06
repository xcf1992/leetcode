/*
445. Add Two Numbers II

You are given two non-empty linked lists representing two non-negative integers.
The most significant digit comes first and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr or l2 == nullptr) {
            return l1 == nullptr ? l2 : l1;
        }

        stack<ListNode*> number1, number2;
        ListNode* current = l1;
        while (current != nullptr) {
            number1.push(current);
            current = current->next;
        }
        current = l2;
        while (current != nullptr) {
            number2.push(current);
            current = current->next;
        }

        int carry = 0;
        ListNode* head = nullptr;
        while (!number1.empty() or !number2.empty() or carry != 0) {
            int sum = carry;
            if (!number1.empty()) {
                sum += number1.top()->val;
                number1.pop();
            }
            if (!number2.empty()) {
                sum += number2.top()->val;
                number2.pop();
            }

            ListNode* node = new ListNode(sum % 10);
            node->next = head;
            head = node;
            carry = sum / 10;
        }
        return head;
    }
};