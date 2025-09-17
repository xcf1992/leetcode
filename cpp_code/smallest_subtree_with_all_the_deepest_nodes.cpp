/*
865. Smallest Subtree with all the Deepest Nodes
https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/

Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.

A node is deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is that node, plus the set of all descendants of that node.

Return the node with the largest depth such that it contains all the deepest nodes in it's subtree.


Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:
      3
    /    \
   5      1
  / \     /\
 6  2    0  8
   / \
  7   4

We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
Both the input and output have TreeNode type.


Note:

The number of nodes in the tree will be between 1 and 500.
The values of each node are unique.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    pair<TreeNode*, int> dfs(TreeNode* root, int depth) {
        if (root == nullptr) {
            return {root, depth - 1};
        }

        pair<TreeNode*, int> leftSub = dfs(root -> left, depth + 1);
        pair<TreeNode*, int> rightSub = dfs(root -> right, depth + 1);
        if (leftSub.second == rightSub.second) {
            return {root, leftSub.second};
        }
        return leftSub.second > rightSub.second ? leftSub : rightSub;
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs(root, 0).first;
    }
};
