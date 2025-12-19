/*
https://leetcode.com/problems/reverse-linked-list-ii/description/
92. Reverse Linked List II

Reverse a linked list from position m to n.
Do it in one-pass.

Note:
1 ≤ m ≤ n ≤ length of list.

Example:
Input: 1->2->3->4->5->nullptr, m = 2, n = 4
Output: 1->4->3->2->5->nullptr
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
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || head->next == nullptr || right == left) {
            return head;
        }

        ListNode* pre_head = new ListNode(-1);
        pre_head->next = head;
        ListNode* pre = pre_head;
        for (int i = 1; i < left; ++i) {
            pre = pre->next;
        }

        if (pre->next == nullptr) {
            return head;
        }

        ListNode* cur = pre->next;
        for (int i = left; i < right; i++) {
            if (cur->next == nullptr) {
                break;
            }

            ListNode* suc = cur->next;
            cur->next = suc->next;
            suc->next = pre->next;
            pre->next = suc;
        }
        return pre_head->next;
    }
};