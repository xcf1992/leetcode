/*
92. Reverse Linked List II
Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->nullptr, m = 2, n = 4
Output: 1->4->3->2->5->nullptr
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode* reverseBetween(ListNode *head, int m, int n) {
        if (head == nullptr or head -> next == nullptr or n == m) {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode* pre = dummy;
        for (int i = 1; i < m; ++i) {
            pre = pre -> next;
        }
        if (pre -> next == nullptr) {
            return head;
        }

        ListNode* cur = pre -> next;
        for (int i = m; i < n; i++) {
            if (cur -> next == nullptr) {
                return dummy -> next;
            }
            ListNode* suc = cur -> next;

            cur -> next = suc -> next;
            suc -> next = pre -> next;
            pre -> next = suc;
        }
        return dummy -> next;
    }
};
