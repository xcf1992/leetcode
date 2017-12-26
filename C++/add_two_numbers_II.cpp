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
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        stack<ListNode*> number1;
        stack<ListNode*> number2;
        ListNode* current = l1;
        while (current != nullptr) {
            number1.push(current);
            current = current -> next;
        }
        current = l2;
        while (current != nullptr) {
            number2.push(current);
            current = current -> next;
        }

        int carry = 0;
        ListNode* head = nullptr;
        while (!number1.empty() && !number2.empty()) {
            int sum = number1.top() -> val + number2.top() -> val + carry;
            ListNode* node = new ListNode(sum % 10);
            node -> next = head;
            head = node;

            number1.pop();
            number2.pop();
            carry = sum / 10;
        }

        if (!number1.empty()) {
            while (!number1.empty()) {
                ListNode* node = number1.top();
                int sum = node -> val + carry;
                node -> val = sum % 10;
                node -> next = head;
                head = node;

                carry = sum / 10;
                number1.pop();
            }
        }
        else if (!number2.empty()) {
            while (!number2.empty()) {
                ListNode* node = number2.top();
                int sum = node -> val + carry;
                node -> val = sum % 10;
                node -> next = head;
                head = node;

                carry = sum / 10;
                number2.pop();
            }
        }

        if (carry != 0) {
            ListNode* node = new ListNode(carry);
            node -> next = head;
            head = node;
        }
        return head;
    }
};

int main() {
    Solution s;
    return 0;
}
