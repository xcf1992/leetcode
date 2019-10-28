/*
138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.

Example 1:
Input:
{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}
Explanation:
Node 1's value is 1, both of its next and random pointer points to Node 2.
Node 2's value is 2, its next pointer points to null and its random pointer points to itself.

Note:
You must return the copy of the given head as a reference to the cloned list.
*/
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

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* cur = head;
        while (cur != nullptr) {
            Node* suc = cur -> next;
            Node* copied = new Node(cur -> val, nullptr, nullptr);
            cur -> next = copied;
            copied -> next = suc;
            cur = suc;
        }

        cur = head;
        while (cur != nullptr) {
            if (cur -> random != nullptr) {
                cur -> next -> random = cur -> random -> next;
            }
            cur = cur -> next -> next;
        }

        Node* newHead = head -> next;
        cur = head;
        Node* cur2 = head -> next;
        while (cur != nullptr) {
            Node* suc = cur2 -> next;
            Node* suc2 = nullptr;
            if (suc != nullptr) {
                suc2 = suc -> next;
            }

            cur -> next = suc;
            cur2 -> next = suc2;
            cur = suc;
            cur2 = suc2;
        }
        return newHead;
    }
};
