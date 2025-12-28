/*
https://leetcode.com/problems/convert-doubly-linked-list-to-array-ii/description/
3294. Convert Doubly Linked List to Array II

You are given an arbitrary node from a doubly linked list, which contains nodes that have a next pointer and a previous
pointer.

Return an integer array which contains the elements of the linked list in order.



Example 1:

Input: head = [1,2,3,4,5], node = 5

Output: [1,2,3,4,5]

Example 2:

Input: head = [4,5,6,7,8], node = 8

Output: [4,5,6,7,8]



Constraints:

The number of nodes in the given list is in the range [1, 500].
1 <= Node.val <= 1000
All nodes have unique Node.val.
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
#include <climits>
using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node() : val(0), next(nullptr), prev(nullptr) {
    }
    Node(int x) : val(x), next(nullptr), prev(nullptr) {
    }
    Node(int x, Node* prev, Node* next) : val(x), next(next), prev(prev) {
    }
};

class Solution {
public:
    vector<int> toArray(Node *node){
        vector<int> rst;
        if (node == nullptr) {
            return rst;
        }

        Node* cur = node;
        while (cur != nullptr) {
            rst.push_back(cur->val);
            cur = cur->prev;
        }
        reverse(rst.begin(), rst.end());

        cur = node->next;
        while (cur != nullptr) {
            rst.push_back(cur->val);
            cur = cur->next;
        }
        return rst;
    }
};