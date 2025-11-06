/*
1367. Linked List in Binary Tree
https://leetcode.com/problems/linked-list-in-binary-tree/

Given a binary tree root and a linked list with head as the first node.
Return True if all the elements in the linked list starting from the head correspond to some downward path connected in
the binary tree otherwise return False. In this context downward path means a path that starts at some node and goes
downwards.

Example 1:
                        1
        4                               4
            2                       2
        1                       6       8
                                       1  3
Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: Nodes in blue form a subpath in the binary Tree.

Example 2:
                        1
        4                               4
            2                       2
        1                       6       8
                                       1  3
Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true

Example 3:
Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: false
Explanation: There is no path in the binary tree that contains all the elements of the linked list from head.

Constraints:
1 <= node.val <= 100 for each node in the linked list and binary tree.
The given linked list will contain between 1 and 100 nodes.
The given binary tree will contain between 1 and 2500 nodes.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    bool dfs(ListNode* head, TreeNode* root) {
        if (head == nullptr) {
            return true;
        }
        if (root == nullptr) {
            return false;
        }
        return root->val == head->val and (dfs(head->next, root->left) or dfs(head->next, root->right));
    }

public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (head == nullptr) {
            return true;
        }
        if (root == nullptr) {
            return false;
        }
        return dfs(head, root) or isSubPath(head, root->left) or isSubPath(head, root->right);
    }
};