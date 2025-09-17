/*
1315. Sum of Nodes with Even-Valued Grandparent
https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/

Given a binary tree, return the sum of values of nodes with even-valued grandparent.
(A grandparent of a node is the parent of its parent, if it exists.)

If there are no nodes with an even-valued grandparent, return 0.

Example 1:
                                    6
                            7               8
                    2           7       1       3
                9             1  4                  5
Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 18
Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.

Constraints:
The number of nodes in the tree is between 1 and 10^4.
The value of nodes is between 1 and 100.
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
    void traverse(TreeNode* root, TreeNode* parent, TreeNode* grandParent, int& result) {
        if (root == nullptr) {
            return;
        }

        if (grandParent != nullptr and (grandParent -> val) % 2 == 0) {
            result += root -> val;
        }
        traverse(root -> left, root, parent, result);
        traverse(root -> right, root, parent, result);
    }
public:
    int sumEvenGrandparent(TreeNode* root) {
        int result = 0;
        traverse(root, nullptr, nullptr, result);
        return result;
    }
};
