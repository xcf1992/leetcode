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

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (head == nullptr) {
            return head;
        }
        if (head->next == nullptr) {
            return head;
        }

        int length = 0;
        ListNode *cur = head;
        while (cur != nullptr) {
            cur = cur->next;
            length++;
        }

        return fuck(head, length);
    }

    ListNode *fuck(ListNode *head, int length) {
        if (length == 1) {
            ListNode *temp = head;
            head = head->next;
            temp->next = nullptr;
            return temp;
        }

        ListNode *left = fuck(head, length / 2);
        ListNode *right = fuck(head, length - length / 2);
        return mergeList(left, right);
    }

    ListNode *mergeList(ListNode *cp1, ListNode *cp2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;

        while (cp1 != nullptr && cp2 != nullptr) {
            if (cp1->val > cp2->val) {
                cur->next = cp2;
                cur = cur->next;
                cp2 = cp2->next;
            }
            else {
                cur->next = cp1;
                cp1 = cp1->next;
                cur = cur->next;
            }
        }

        while (cp1 != nullptr) {
            cur->next = cp1;
            cp1 = cp1->next;
            cur = cur->next;
        }
        while (cp2 != nullptr) {
            cur->next = cp2;
            cp2 = cp2->next;
            cur = cur->next;
        }

        return dummy->next;
    }
};

int main() {
	Solution s;
	ListNode *head = new ListNode(2);
	ListNode *n = new ListNode(1);
	head->next = n;
	s.sortList(head);
	return 0;
}