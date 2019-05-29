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
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        int length = 0;
        ListNode *pre = dummy;
        while (pre -> next != nullptr) {
            length++;
            pre = pre->next;
        }

        k = k % length;
        if (k == 0) {
            return head;
        }

        pre = dummy;
        ListNode *first = dummy->next;
        ListNode *second = first;
        for (int i = 1; i < k; i++) {
            second = second->next;
        }

        while (second->next != nullptr) {
            second = second->next;
            first = first->next;
            pre = pre->next;
        }

        pre->next = nullptr;
        second->next = head;
        return first;
    }
};

int main() {
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	Solution s;
	s.rotateRight(head, 2);
	return 0;
}