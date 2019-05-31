/*
369. Plus One Linked List
Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4
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
using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
  };

class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        
        stack<ListNode*> stk;
        ListNode* cur = head;
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur -> next;
        }
        
        int add = 1;
        while (!stk.empty()) {
            cur = stk.top();
            stk.pop();
            
            int sum = cur -> val + add;
            cur -> val = sum % 10;
            add = sum / 10;
        }
        
        if (add == 0) {
            return head;
        }
        
        ListNode* newHead = new ListNode(1);
        newHead -> next = head;
        return newHead;
    }
};

class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        ListNode* cur = head;
        ListNode* start = cur;
        ListNode* last;

        while (cur != nullptr) {
            if (cur -> val == 9) {
                start = cur;
                while (cur -> next != nullptr && cur -> next -> val == 9) {
                    cur = cur -> next;
                }
            }
            if (cur != nullptr) {
                if (cur -> next == nullptr) {
                    last = cur;
                }
                cur = cur -> next;
            }
        }

        if (last -> val != 9) {
            last -> val += 1;
            return head;
        }

        if (start == head) {
            ListNode* newHead = new ListNode(1);
            newHead -> next = head;
            for (ListNode* it = start; it != nullptr; it = it -> next) {
                it -> val = 0;
            }
            return newHead;
        }

        ListNode* it = head;
        while (it != nullptr) {
            if (it -> next == start) {
                it -> val += 1;
                it = it -> next;
                while (it != nullptr) {
                    it -> val = 0;
                    it = it -> next;
                }
            }
            if (it != nullptr) {
                it = it -> next;
            }
        }
        return head;
    }
};

class Solution1 {
private:
    ListNode* reverse(ListNode* head) {
        ListNode* cur = head -> next;
        head -> next = nullptr;
        while (cur != nullptr) {
            ListNode* next = cur -> next;

            cur -> next = head;
            head = cur;
            cur = next;
        }
        return head;
    }

    ListNode* plus(ListNode* head) {
        ListNode* cur = head;
        ListNode* last = nullptr;
        while (cur != nullptr) {
            if (cur -> val == 9) {
                cur -> val = 0;
                last = cur;
            }
            else {
                cur -> val += 1;
                break;
            }
            cur = cur -> next;
        }
        if (cur == nullptr) {
            last -> next = new ListNode(1);
        }
        return head;
    }
public:
    ListNode* plusOne(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        head = reverse(head);
        head = plus(head);
        head = reverse(head);
        return head;
    }
};