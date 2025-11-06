/*
1721. Swapping Nodes in a Linked List
https://leetcode.com/problems/swapping-nodes-in-a-linked-list/

You are given the head of a linked list, and an integer k.
Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from
the end (the list is 1-indexed).

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Example 2:
Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
Example 3:
Input: head = [1], k = 1
Output: [1]
Example 4:
Input: head = [1,2], k = 1
Output: [2,1]
Example 5:
Input: head = [1,2,3], k = 2
Output: [1,2,3]

Constraints:
The number of nodes in the list is n.
1 <= k <= n <= 105
0 <= Node.val <= 100
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
#include <stdio.h>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode *n1 = nullptr, *n2 = nullptr;
        for (auto p = head; p != nullptr; p = p->next) {
            n2 = n2 == nullptr ? nullptr : n2->next;
            if (--k == 0) {
                n1 = p;
                n2 = head;
            }
        }
        swap(n1->val, n2->val);
        return head;
    }
};