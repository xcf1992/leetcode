/*
708. Insert into a Cyclic Sorted List
https://leetcode.com/problems/insert-into-a-cyclic-sorted-list/

Given a node from a cyclic linked list which is sorted in ascending order,
write a function to insert a value into the list such that it remains a cyclic sorted list.
The given node can be a reference to any single node in the list,
and may not be necessarily the smallest value in the cyclic list.

If there are multiple suitable places for insertion,
you may choose any place to insert the new value.
After the insertion, the cyclic list should remain sorted.

If the list is empty (i.e., given node is null),
you should create a new single cyclic list and return the reference to that single node.
Otherwise, you should return the original given node.

The following example may help you understand the problem better:
1-------------
^             |
|             |
|             V
2 <-----------3 <----head
In the figure above, there is a cyclic sorted list of three elements.

You are given a reference to the node with value 3, and we need to insert 2 into the list.
1-------------2
^             |
|             |
|             V
2 <-----------3 <----head

The new node should insert between node 1 and node 3.
After the insertion, the list should look like this, and we should still return node 3.
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
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* newNode = new Node(insertVal, nullptr);
        if (head == nullptr) {
            newNode -> next = newNode;
            return newNode;
        }

        Node* cur = head;
        Node* biggestNode = cur;
        do {
            Node* suc = cur -> next;
            if (cur -> val <= insertVal and suc -> val >= insertVal) {
                cur -> next = newNode;
                newNode -> next = suc;
                return head;
            }
            cur = suc;
            suc = cur -> next;
            if (cur -> val >= biggestNode -> val) {
                biggestNode = cur;
            }
        } while (cur != head);

        newNode -> next = biggestNode -> next;
        biggestNode -> next = newNode;
        return head;
    }
};
