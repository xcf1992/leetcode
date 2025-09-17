/*
141. Linked List Cycle
Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list,
we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to.
If pos is -1, then there is no cycle in the linked list.

Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.

Follow up:
Can you solve it using O(1) (i.e. constant) memory?
*/
#include <iostream>
#include <sstream>
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
    bool hasCycle(ListNode* head) {
        if (head == nullptr or head -> next == nullptr) {
            return false;
        }

        if (head -> next == head) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = slow -> next;
        while (slow != fast and fast != nullptr) {
            fast = fast -> next;
            if (fast != nullptr) {
                slow = slow -> next;
                fast = fast -> next;
            }
        }
        return fast == slow;
    }
};
