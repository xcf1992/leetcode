/*
 1008. Construct Binary Search Tree from Preorder Traversal
 
 Return the root node of a binary search tree that matches the given preorder traversal.
 
 (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)
 
 
 
 Example 1:
 
 Input: [8,5,1,7,10,12]
 Output: [8,5,10,1,7,null,12]
 
 
 
 Note:
 
 1 <= preorder.length <= 100
 The values of preorder are distinct.
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
private:
    TreeNode* construct(int start, int end, vector<int> num) {
        if (start >= end) {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(num[start]);
        int l = start + 1;
        int r = l;
        while (r < end and num[r] < num[start]) {
            r += 1;
        }
        root -> left = construct(l, r, num);
        root -> right = construct(r, end, num);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return construct(0, preorder.size(), preorder);
    }
};
