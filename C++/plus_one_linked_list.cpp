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
    ListNode* plusOne(ListNode* head) {
        ListNode* cur = head;
        ListNode* start = cur;
        ListNode* last;

        while (cur != nullptr) {
            if (cur -> val == 9) {
                start = cur;
                while (cur -> next != nullptr && cur -> next -> val == 9) {
                    cur = cur -> next;
                }
            }
            if (cur != nullptr) {
                if (cur -> next == nullptr) {
                    last = cur;
                }
                cur = cur -> next;
            }
        }

        if (last -> val != 9) {
            last -> val += 1;
            return head;
        }

        if (start == head) {
            ListNode* newHead = new ListNode(1);
            newHead -> next = head;
            for (ListNode* it = start; it != nullptr; it = it -> next) {
                it -> val = 0;
            }
            return newHead;
        }

        ListNode* it = head;
        while (it != nullptr) {
            if (it -> next == start) {
                it -> val += 1;
                it = it -> next;
                while (it != nullptr) {
                    it -> val = 0;
                    it = it -> next;
                }
            }
            if (it != nullptr) {
                it = it -> next;
            }
        }
        return head;
    }
};

int main() {
    Solution s;
    return 0;
}