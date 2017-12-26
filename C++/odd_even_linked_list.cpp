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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head -> next == nullptr || head -> next -> next == nullptr) {
            return head;
        }

        ListNode* oddCur = head;
        ListNode* evenCur = head -> next;
        ListNode* cur = evenCur -> next;
        int num = 3;
        while (cur != nullptr) {
            ListNode* nextNode = cur -> next;

            if (num % 2) {
                evenCur -> next = nextNode;
                cur -> next = oddCur -> next;
                oddCur -> next = cur;
                oddCur = oddCur -> next;
            }
            else {
                evenCur = evenCur -> next;
            }

            cur = nextNode;
            num += 1;
        }

        return head;
    }
};

int main() {
    Solution s;
    return 0;
}