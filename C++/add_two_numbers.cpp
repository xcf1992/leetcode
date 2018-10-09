/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

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
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        int flag = 0;
        ListNode *cur1 = l1;
        ListNode *cur2 = l2;
        ListNode *head = new ListNode(-1);
        head -> next = l1;
        ListNode *cur = head;
        while (cur1 != nullptr && cur2 != nullptr) {
            int a = cur1 -> val;
            int b = cur2 -> val;

            int sum = a + b + flag;
            int digit = sum % 10;
            flag = sum / 10;
            
            cur -> next -> val = digit;
            cur = cur -> next;
            
            cur1 = cur1 -> next;
            cur2 = cur2 -> next;
        }
        
        while (cur1 != nullptr) {
            int a = cur1 -> val;
            int sum = a + flag;
            cur1 -> val = sum % 10;
            flag = sum / 10;
            cur -> next = cur1;
            cur = cur -> next;
            cur1 = cur1 -> next;
        }
        while (cur2 != nullptr) {
            int b = cur2 -> val;
            int sum = b + flag;
            cur2 -> val = sum % 10;
            flag = sum / 10;
            cur -> next = cur2;
            cur = cur -> next;
            cur2 = cur2 -> next;
        }
        if (flag == 1) {
            cur -> next = new ListNode(flag);
        }
        
        return head->next;
    }
};