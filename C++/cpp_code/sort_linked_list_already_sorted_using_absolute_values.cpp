/*
https://leetcode.com/problems/sort-linked-list-already-sorted-using-absolute-values/description/
2046. Sort Linked List Already Sorted Using Absolute Values

Given the head of a singly linked list that is sorted in non-decreasing order using the absolute values of its nodes,
return the list sorted in non-decreasing order using the actual values of its nodes.


Example 1:


Input: head = [0,2,-5,5,10,-10]
Output: [-10,-5,0,2,5,10]
Explanation:
The list sorted in non-descending order using the absolute values of the nodes is [0,2,-5,5,10,-10].
The list sorted in non-descending order using the actual values is [-10,-5,0,2,5,10].
Example 2:


Input: head = [0,1,2]
Output: [0,1,2]
Explanation:
The linked list is already sorted in non-decreasing order.
Example 3:

Input: head = [1]
Output: [1]
Explanation:
The linked list is already sorted in non-decreasing order.


Constraints:

The number of nodes in the list is the range [1, 105].
-5000 <= Node.val <= 5000
head is sorted in non-decreasing order using the absolute value of its nodes.


Follow up:
Can you think of a solution with O(n) time complexity?
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
public:
    ListNode* sortLinkedList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        while (curr != nullptr) {
            if (curr -> val >= 0) {
                curr = curr -> next;
                prev = prev -> next;
                continue;
            }

            prev->next = curr->next;
            curr->next = head;
            head = curr;
            curr = prev->next;
        }
        return head;
    }
};

class Solution {
public:
    ListNode* sortLinkedList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prev = head;
        ListNode* cur = head->next;
        while (cur != nullptr) {
            if (cur -> val >= 0) {
                cur = cur -> next;
                prev = prev -> next;
                continue;
            }

            prev->next = cur->next;
            cur->next = dummy->next;
            dummy->next = cur;
            cur = prev->next;
        }
        return dummy->next;
    }
};