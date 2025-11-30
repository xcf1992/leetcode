/*
21. Merge Two Sorted Lists
https://leetcode.com/problems/merge-two-sorted-lists/

Merge two sorted linked lists and return it as a new list.
The new list should be made by splicing together the nodes of the first two lists.

Example:
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
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
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
    // recursive
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr or l2 == nullptr) {
            return l1 == nullptr ? l2 : l1;
        }

        if (l1->val > l2->val) {
            swap(l1, l2);
        }
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
};

class Solution1 {
    // iterative
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr or l2 == nullptr) {
            return l1 == nullptr ? l2 : l1;
        }

        ListNode* dummy = new ListNode(-1);
        ListNode* pre = dummy;
        while (l1 != nullptr or l2 != nullptr) {
            if (l1 == nullptr or (l2 != nullptr and l1->val > l2->val)) {
                pre->next = l2;
                l2 = l2->next;
            } else {
                pre->next = l1;
                l1 = l1->next;
            }
            pre = pre->next;
        }
        return dummy->next;
    }
};