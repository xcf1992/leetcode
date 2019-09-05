/*
83. Remove Duplicates from Sorted List

Given a sorted linked list, delete all duplicates such that each element appear only once.

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
using namespace std;

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr || head -> next == nullptr) {
            return head;
        }

        ListNode * current = head;
        while (current -> next != nullptr) {
            ListNode * nextnode = current -> next;
            if (current -> val == nextnode -> val) {
                current -> next = nextnode -> next;
                delete nextnode;
            }
            else {
                current = current->next;
            }
        }

        return head;
    }
};
