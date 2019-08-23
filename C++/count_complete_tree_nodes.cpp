/*
222. Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level,
except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input:
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
*/
#include <iostream>
#include <sstream>
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
/*
Explanation

The height of a tree can be found by just going left.
Let a single node tree have height 0.
Find the height h of the whole tree.
If the whole tree is empty, i.e., has height -1, there are 0 nodes.

Otherwise check whether the height of the right subtree is just one less than that of the whole tree,
meaning left and right subtree have the same height.

If yes,
then the last node on the last tree row is in the right subtree
and the left subtree is a full tree of height h-1.
So we take the 2^h-1 nodes of the left subtree plus the 1 root node
plus recursively the number of nodes in the right subtree.

If no,
then the last node on the last tree row is in the left subtree
and the right subtree is a full tree of height h-2.
So we take the 2^(h-1)-1 nodes of the right subtree plus the 1 root node
plus recursively the number of nodes in the left subtree.

Since I halve the tree in every recursive step, I have O(log(n)) steps. Finding a height costs O(log(n)). So overall O(log(n)^2).
*/
class Solution {
private:
    int getHeight(TreeNode* root) {
        return root == nullptr ? -1 : 1 + getHeight(root -> left);
    }
public:
    int countNodes(TreeNode* root) {
        int h = getHeight(root);
        if (h < 0) {
            return 0;
        }
        if (getHeight(root -> right) == h - 1) {
            return (1 << h) + countNodes(root -> right);
        }
        return (1 << (h - 1)) + countNodes(root -> left);
    }
};

class Solution1 {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = 1;
        TreeNode* leftC = root -> left;
        while (leftC != nullptr) {
            leftC = leftC -> left;
            leftHeight += 1;
        }

        int rightHeight = 1;
        TreeNode* rightC = root -> right;
        while (rightC != nullptr) {
            rightC = rightC -> right;
            rightHeight += 1;
        }
        return leftHeight == rightHeight ? pow(2, leftHeight) - 1 : 1 + countNodes(root -> left) + countNodes(root -> right);
    }
};
