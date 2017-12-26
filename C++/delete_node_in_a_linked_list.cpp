#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
    void deleteNode(ListNode* node) {
        if (node == nullptr) {
            return;
        }

        ListNode* nextNode = node -> next;
        node -> val = nextNode -> val;
        node -> next = nextNode -> next;
        delete(nextNode);
        nextNode = nullptr;

        return;
    }
};

int main() {
    Solution s;
    return 0;
}