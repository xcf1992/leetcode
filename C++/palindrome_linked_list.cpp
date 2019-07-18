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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head -> next == nullptr) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast -> next != nullptr && fast -> next -> next != nullptr) {
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        ListNode* reverseHead = slow -> next;
        ListNode* cur = reverseHead -> next;
        reverseHead -> next = nullptr;
        ListNode* nextNode = nullptr;
        while (cur != nullptr) {
            nextNode = cur -> next;
            cur -> next = reverseHead;
            reverseHead = cur;
            cur = nextNode;
        }

        cur = reverseHead;
        slow = head;
        while (cur != nullptr && slow != nullptr) {
            if (cur -> val != slow -> val) {
                return false;
            }
            cur = cur -> next;
            slow = slow -> next;
        }
        return true;
    }
};

int main() {
    Solution s;
    return 0;
}