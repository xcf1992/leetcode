/*
82. Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
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
using namespace std;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode *head) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;

        ListNode* pre = dummy;
        ListNode* cur = head;
        while (cur != nullptr and cur -> next != nullptr) {
            ListNode* suc = cur -> next;
            if (suc -> val == cur -> val) {
                while (suc != nullptr and suc -> val == cur -> val) {
                    suc = suc -> next;
                }
                pre -> next = suc;
                cur = suc;
            }
            else {
                pre = cur;
                cur = suc;
            }
        }
        return dummy->next;
    }
};
