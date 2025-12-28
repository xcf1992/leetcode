/*
https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/description/
2816. Double a Number Represented as a Linked List

You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.

Return the head of the linked list after doubling it.



Example 1:


Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned
linked list represents the number 189 * 2 = 378. Example 2:


Input: head = [9,9,9]
Output: [1,9,9,8]
Explanation: The figure above corresponds to the given linked list which represents the number 999. Hence, the returned
linked list reprersents the number 999 * 2 = 1998.


Constraints:

The number of nodes in the list is in the range [1, 104]
0 <= Node.val <= 9
The input is generated such that the list represents a number that does not have leading zeros, except the number 0
itself.
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
private:
    ListNode* reverse(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }

public:
    ListNode* doubleIt(ListNode* head) {
        if (head == nullptr) {
            return head;
        }

        head = reverse(head);
        int carry = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            int val = curr->val;
            curr->val = (carry + 2 * val) % 10;
            carry = (carry + 2 * val) / 10;
            curr = curr->next;
        }

        head = reverse(head);
        if (carry == 0) {
            return head;
        }

        ListNode* new_head = new ListNode(carry, head);
        return new_head;
    }
};