#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        int flag = 0;
        ListNode *cur1 = l1;
        ListNode *cur2 = l2;
        ListNode *head = new ListNode(-1);
        head->next = l1;
        ListNode *cur = head;
        while (cur1 != nullptr && cur2 != nullptr) {
            int a = cur1->val;
            int b = cur2->val;
            int sum = a + b + flag;

            int digit = sum % 10;
            int flag = sum / 10;

            cur->next->val = digit;
            cur = cur->next;

            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        while (cur1 != nullptr) {
            int a = cur1->val;
            int sum = a + flag;
            cur1->val = sum % 10;
            flag = sum / 10;
            cur->next = cur1;
            cur = cur->next;
            cur1 = cur1->next;
        }
        while (cur2 != nullptr) {
            int b = cur2->val;
            int sum = b + flag;
            cur2->val = sum % 10;
            flag = sum / 10;
            cur->next = cur2;
            cur = cur->next;
            cur2 = cur2->next;
        }
        if (flag == 1) {
            cur->next = new ListNode(flag);
        }

        return head->next;
    }

int main() {
	ListNode * l1 = new ListNode(5);
	ListNode * l2 = new ListNode(5);
	addTwoNumbers(l1, l2);
	return 0;
}