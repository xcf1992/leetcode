/*
 Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
 
 Note: If the given node has no in-order successor in the tree, return null.
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
#include <set>
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Solution {
private:
    TreeNode* leftMostNode(TreeNode* root) {
        while (root -> left) {
            root = root -> left;
        }
        return root;
    }
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p -> right) {
            return leftMostNode(p -> right);
        }
        
        TreeNode* suc = nullptr;
        TreeNode* cur = root;
        while (cur) {
            if (p -> val < cur -> val) {
                suc = cur;
                cur = cur -> left;
            }
            else if (p -> val > cur -> val) {
                cur = cur -> right;
            }
            else {
                break;
            }
        }
        return suc;
    }
};
