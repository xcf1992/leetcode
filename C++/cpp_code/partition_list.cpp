/*
86. Partition List
https://leetcode.com/problems/partition-list/

Given a linked list and a value x,
partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
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

using namespace std;

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* smaller = new ListNode(-1);
        ListNode* first = smaller;
        ListNode* greater = new ListNode(-1);
        ListNode* second = greater;
        while (head != nullptr) {
            if (head->val < x) {
                first->next = head;
                first = first->next;
            } else {
                second->next = head;
                second = second->next;
            }
            head = head->next;
        }
        first->next = greater->next;
        second->next = nullptr;
        return smaller->next;
    }
};