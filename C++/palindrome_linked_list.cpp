/*
234. Palindrome Linked List
Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr or head -> next == nullptr) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr) {
            fast = fast -> next;
            if (fast != nullptr) {
                slow = slow -> next;
                fast = fast -> next;
            }
        }

        ListNode* reverseHead = slow;
        ListNode* cur = reverseHead -> next;
        reverseHead -> next = nullptr;
        while (cur != nullptr) {
            ListNode* suc = cur -> next;
            cur -> next = reverseHead;
            reverseHead = cur;
            cur = suc;
        }

        cur = reverseHead;
        slow = head;
        while (cur != nullptr and slow != nullptr) {
            if (cur -> val != slow -> val) {
                return false;
            }
            cur = cur -> next;
            slow = slow -> next;
        }
        return true;
    }
};
