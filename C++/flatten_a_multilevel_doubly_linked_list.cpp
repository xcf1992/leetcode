/*
 You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, which may or may not point to a separate doubly linked list. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure, as shown in the example below.

 Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.

 Example:

 Input:
 1---2---3---4---5---6--NULL
 |
 7---8---9---10--NULL
 |
 11--12--NULL

 Output:
 1-2-3-7-8-11-12-9-10-4-5-6-NULL
 Explanation for the above example:

 Given the following multilevel doubly linked list:



 We should return the following flattened doubly linked list:
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
using namespace std;


 class Node {
 public:
 int val = NULL;
 Node* prev = NULL;
 Node* next = NULL;
 Node* child = NULL;

 Node() {}

 Node(int _val, Node* _prev, Node* _next, Node* _child) {
 val = _val;
 prev = _prev;
 next = _next;
 child = _child;
 }
 };

class Solution {
public:
    Node* flatten(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* cur = head;
        while (cur != nullptr) {
            if (cur -> child == nullptr) {
                cur = cur -> next;
            }
            else {
                Node* childHead = flatten(cur -> child);
                Node* childLast = childHead;
                while (childLast -> next != nullptr) {
                    childLast = childLast -> next;
                }
                if (cur -> next != nullptr) {
                    childLast -> next = cur -> next;
                    cur -> next -> prev = childLast;
                }
                cur -> next = childHead;
                childHead -> prev = cur;

                cur -> child = nullptr;
                cur = childLast -> next;
            }
        }
        return head;
    }
};
