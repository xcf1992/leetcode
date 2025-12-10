/*
99. Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    void traverse(TreeNode* root, TreeNode*& prev, TreeNode*& first, TreeNode*& second) {
        if (root == nullptr) {
            return;
        }

        traverse(root->left, prev, first, second);
        /*
         * there are two cases one is swap adjacent elements, so it will be like 1, 3, 2
         * then we will need to identify 3 with prev and 2 with root
         * Second case is 1,4,3,2
         * Then when we first time find prev > root, we identify 4 as first 3 as second
         * and second time we find 3 > 2, we do no change first which is 4 but only update second to be 2
         */
        if (prev != nullptr and prev->val >= root->val) {
            if (first == nullptr) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        traverse(root->right, prev, first, second);
    }

public:
    void recoverTree(TreeNode* root) {
        TreeNode* prev = nullptr;
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        traverse(root, prev, first, second);
        swap(first->val, second->val);
    }
};