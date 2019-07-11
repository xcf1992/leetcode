#include <iostream>
#include <string>
#include <vector>
/*
671. Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative value,
where each node in this tree has exactly two or zero sub-node.
If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.
More formally, the property root.val = min(root.left.val, root.right.val) always holds.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:

Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.


Example 2:

Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
*/
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    void search(TreeNode* root, int& minVal, int& result) {
        if (root == nullptr) {
            return;
        }

        if (root -> val > minVal and (result == -1 or root -> val < result)) {
            result = root -> val;
            return;
        }

        if (root -> val == minVal) {
            search(root -> left, minVal, result);
            search(root -> right, minVal, result);
        }
    }
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (root == nullptr) {
            return -1;
        }

        int minVal = root -> val;
        int result = -1;
        search(root, minVal, result);
        return result != -1 ? result : -1;
    }
};
