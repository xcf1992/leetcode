/*
 Given a binary tree with N nodes, each node has a different value from {1, ..., N}.
 
 A node in this binary tree can be flipped by swapping the left child and the right child of that node.
 
 Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.
 
 (Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)
 
 Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.
 
 If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.
 
 If we cannot do so, then return the list [-1].
 
 
 
 Example 1:
 
 
 
 Input: root = [1,2], voyage = [2,1]
 Output: [-1]
 Example 2:
 
 
 
 Input: root = [1,2,3], voyage = [1,3,2]
 Output: [1]
 Example 3:
 
 
 
 Input: root = [1,2,3], voyage = [1,2,3]
 Output: []
 
 
 Note:
 
 1 <= N <= 100
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
    bool traversal(TreeNode* root, vector<int>& voyage, vector<int>& result, int& cur) {
        if (root == nullptr) {
            return true;
        }
        
        if (root -> val != voyage[cur]) {
            return false;
        }
        
        cur += 1;
        if (cur == voyage.size()) {
            return true;
        }
        
        if (root -> left != nullptr) {
            if (root -> left -> val != voyage[cur]) {
                if (root -> right != nullptr and root -> right -> val == voyage[cur]) {
                    swap(root -> left, root -> right);
                    result.push_back(root -> val);
                }
                else {
                    return false;
                }
            }
            
            if (!traversal(root -> left, voyage, result, cur)) {
                return false;
            }
        }
        
        if (!traversal(root -> right, voyage, result, cur)) {
            return false;
        }
        return true;
    }
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        int cur = 0;
        if (!traversal(root, voyage, result, cur)) {
            return {-1};
        }
        return result;
    }
};
