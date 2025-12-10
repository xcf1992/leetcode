/*
328. Odd Even Linked List

Given a singly linked list, group all odd nodes together followed by the even nodes.
Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL

Example 2:
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...
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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr or head->next == nullptr) {
            return head;
        }

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even;
        while (even != nullptr and even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};

class Solution1 {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr or head->next == nullptr or head->next->next == nullptr) {
            return head;
        }

        ListNode* oddCur = head;
        ListNode* evenCur = head->next;
        ListNode* cur = evenCur->next;
        int num = 3;
        while (cur != nullptr) {
            ListNode* nextNode = cur->next;

            if (num % 2) {
                evenCur->next = nextNode;
                cur->next = oddCur->next;
                oddCur->next = cur;
                oddCur = oddCur->next;
            } else {
                evenCur = evenCur->next;
            }

            cur = nextNode;
            num += 1;
        }

        return head;
    }
};