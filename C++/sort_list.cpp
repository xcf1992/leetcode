/*
148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    ListNode* mergeList(ListNode *cp1, ListNode *cp2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;

        while (cp1 != nullptr or cp2 != nullptr) {
            if (cp1 == nullptr or (cp2 != nullptr and cp1 -> val > cp2 -> val)) {
                cur -> next = cp2;
                cp2 = cp2 -> next;
            }
            else {
                cur->next = cp1;
                cp1 = cp1->next;
            }
            cur = cur -> next;
        }
        return dummy -> next;
    }
public:
    ListNode* sortList(ListNode *head) {
        if (head == nullptr or head -> next == nullptr) {
            return head;
        }

        ListNode* pre = new ListNode(-1);
        ListNode* fast = head;
        ListNode* slow = head;
        pre -> next = slow;
        while (fast != nullptr) {
            fast = fast -> next;
            if (fast != nullptr) {
                fast = fast -> next;
                slow = slow -> next;
                pre = pre -> next;
            }
        }
        pre -> next = nullptr;

        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(slow);
        return mergeList(l1, l2);
    }
};
