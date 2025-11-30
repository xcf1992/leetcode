/*
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.
You may not modify the values in the list's nodes, only nodes itself may be changed.

Example:
Given 1->2->3->4, you should return the list as 2->1->4->3.
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
#include <climits>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* first = head;
        ListNode* second = head->next;
        ListNode* pre = dummy;
        while (first != nullptr and second != nullptr) {
            ListNode* suc = second->next;
            pre->next = second;
            second->next = first;
            first->next = suc;

            pre = first;
            first = suc;
            if (first != nullptr) {
                second = first->next;
            }
        }
        return dummy->next;
    }
};