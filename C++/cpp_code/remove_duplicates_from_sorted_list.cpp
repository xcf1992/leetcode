/*
83. Remove Duplicates from Sorted List
https://leetcode.com/problems/remove-duplicates-from-sorted-list/

Given a sorted linked list,
delete all duplicates such that each element appear only once.

Example 1:
Input: 1->1->2
Output: 1->2

Example 2:
Input: 1->1->2->3->3
Output: 1->2->3
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr or
        head->next == nullptr
        )
        {
            return head;
        }

        ListNode *current = head;
        while (current->next != nullptr) {
            ListNode *suc = current->next;
            if (current->val == suc->val) {
                current->next = suc->next;
                delete suc;
                suc = nullptr;
            } else {
                current = current->next;
            }
        }
        return head;
    }
};