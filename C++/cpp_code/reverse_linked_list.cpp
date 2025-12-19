/*
https://leetcode.com/problems/reverse-linked-list/description/
206. Reverse Linked List

Reverse a singly linked list.

Example:
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

Follow up:
A linked list can be reversed either iteratively or recursively. Could you implement both?
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

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {
    }
    ListNode(int x) : val(x), next(nullptr) {
    }
    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class Solution {
    // iterative
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* suc = cur->next;
            cur->next = prev;
            prev = cur;
            cur = suc;
        }
        return prev;
    }
};

class Solution1 {
    // recursive
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* reverseHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return reverseHead;
    }
};