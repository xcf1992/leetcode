/*
237. Delete Node in a Linked List
Write a function to delete a node (except the tail) in a singly linked list,
given only access to that node.

Given linked list -- head = [4,5,1,9], which looks like following:
4 --> 5 --> 1 --> 9
Example 1:

Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.
Example 2:

Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.


Note:

The linked list will have at least two elements.
All of the nodes' values will be unique.
The given node will not be the tail and it will always be a valid node of the linked list.
Do not return anything from your function.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

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
    }
};
